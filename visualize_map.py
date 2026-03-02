#!/usr/bin/env python3
"""
visualize_map.py — View the cave voxel-map PLY output from the autosys13 mission.

Usage:
    python3 visualize_map.py               # auto-picks latest /output/mission_*_map.ply
    python3 visualize_map.py /output/my.ply   # explicit file
    python3 visualize_map.py --matplotlib  # force matplotlib (no open3d needed)

Open3D is used when available (interactive rotate/zoom). On first run it is
installed automatically via pip.  Matplotlib is the fallback.
"""

import sys
import os
import glob
import argparse
import subprocess


# ---------------------------------------------------------------------------
# Argument parsing
# ---------------------------------------------------------------------------

parser = argparse.ArgumentParser(description="Visualize cave map PLY")
parser.add_argument("file", nargs="?", help="Path to .ply file (default: latest in /output)")
parser.add_argument("--matplotlib", action="store_true", help="Force matplotlib backend")
parser.add_argument("--max-points", type=int, default=500_000,
                    help="Downsample if cloud is larger than this (default 500k)")
args = parser.parse_args()


# ---------------------------------------------------------------------------
# Find the PLY file
# ---------------------------------------------------------------------------

def find_latest_ply():
    candidates = sorted(glob.glob("/output/mission_*_map.ply"), reverse=True)
    if candidates:
        return candidates[0]
    # Also check current directory
    candidates = sorted(glob.glob("*.ply"), reverse=True)
    if candidates:
        return candidates[0]
    return None


ply_path = args.file
if ply_path is None:
    ply_path = find_latest_ply()
    if ply_path is None:
        print("No PLY file found. Either:")
        print("  • Run the mission first (map saves to /output/mission_*_map.ply on LAND/COMPLETE)")
        print("  • Or: ros2 service call /mapping/save_map utils/srv/SaveMap "
              "\"{output_path: '/output/map.ply', format: 'ply'}\"")
        print("  • Or pass the path explicitly: python3 visualize_map.py /path/to/map.ply")
        sys.exit(1)

if not os.path.exists(ply_path):
    print(f"File not found: {ply_path}")
    sys.exit(1)

print(f"Loading: {ply_path}")


# ---------------------------------------------------------------------------
# PLY parser (pure Python — no external deps needed for reading)
# ---------------------------------------------------------------------------

import struct

def load_ply(path):
    """Returns (x, y, z, r, g, b) numpy arrays. Handles ASCII and binary PLY."""
    import numpy as np

    with open(path, "rb") as f:
        # Parse header
        header_lines = []
        while True:
            line = f.readline().decode("utf-8", errors="replace").strip()
            header_lines.append(line)
            if line == "end_header":
                break

        n_vertices = 0
        properties = []
        fmt = "ascii"
        for line in header_lines:
            if line.startswith("element vertex"):
                n_vertices = int(line.split()[-1])
            elif line.startswith("property"):
                parts = line.split()
                properties.append((parts[1], parts[2]))  # (dtype, name)
            elif line.startswith("format"):
                fmt = line.split()[1]

        has_color = any(p[1] in ("red", "green", "blue") for p in properties)

        if fmt == "ascii":
            data = []
            for _ in range(n_vertices):
                row = f.readline().decode("utf-8", errors="replace").split()
                data.append([float(v) for v in row])
            data = np.array(data, dtype=np.float32)
            x, y, z = data[:, 0], data[:, 1], data[:, 2]
            if has_color and data.shape[1] >= 6:
                r = data[:, 3].astype(np.uint8)
                g = data[:, 4].astype(np.uint8)
                b = data[:, 5].astype(np.uint8)
            else:
                r = g = b = None
        else:
            # Binary PLY
            prop_fmt = []
            for dtype, name in properties:
                if dtype in ("float", "float32"):
                    prop_fmt.append(("f", 4))
                elif dtype in ("double", "float64"):
                    prop_fmt.append(("d", 8))
                elif dtype in ("uchar", "uint8"):
                    prop_fmt.append(("B", 1))
                elif dtype in ("int", "int32"):
                    prop_fmt.append(("i", 4))
                else:
                    prop_fmt.append(("f", 4))
            row_size = sum(s for _, s in prop_fmt)
            raw = f.read(n_vertices * row_size)
            endian = "<" if "little" in fmt else ">"
            struct_fmt = endian + "".join(c for c, _ in prop_fmt)
            rows = struct.iter_unpack(struct_fmt, raw)
            data = np.array(list(rows), dtype=np.float32)
            x, y, z = data[:, 0], data[:, 1], data[:, 2]
            prop_names = [p[1] for p in properties]
            if "red" in prop_names and has_color:
                ri = prop_names.index("red")
                gi = prop_names.index("green")
                bi = prop_names.index("blue")
                r = data[:, ri].astype(np.uint8)
                g = data[:, gi].astype(np.uint8)
                b = data[:, bi].astype(np.uint8)
            else:
                r = g = b = None

    return x, y, z, r, g, b, n_vertices


x, y, z, r, g, b, n_total = load_ply(ply_path)
print(f"  {n_total:,} voxels loaded  |  "
      f"X [{x.min():.1f} → {x.max():.1f}]  "
      f"Y [{y.min():.1f} → {y.max():.1f}]  "
      f"Z [{z.min():.1f} → {z.max():.1f}]  metres")

# Downsample if too large for interactive display
import numpy as np
if n_total > args.max_points:
    print(f"  Downsampling {n_total:,} → {args.max_points:,} points for display")
    idx = np.random.choice(n_total, args.max_points, replace=False)
    x, y, z = x[idx], y[idx], z[idx]
    if r is not None:
        r, g, b = r[idx], g[idx], b[idx]

# Build normalised colour array (0-1 floats)
if r is not None:
    colors = np.stack([r, g, b], axis=1).astype(np.float32) / 255.0
else:
    # Fallback: height-based viridis colouring in Python
    t = (z - z.min()) / max(z.max() - z.min(), 1e-6)
    import matplotlib.cm as cm
    colors = cm.viridis(t)[:, :3].astype(np.float32)


# ---------------------------------------------------------------------------
# Visualise — Open3D first, matplotlib fallback
# ---------------------------------------------------------------------------

USE_O3D = not args.matplotlib

if USE_O3D:
    try:
        import open3d as o3d
    except ImportError:
        print("open3d not found — installing (this takes ~30s once) …")
        subprocess.check_call([sys.executable, "-m", "pip", "install", "open3d", "-q"])
        import open3d as o3d

    pcd = o3d.geometry.PointCloud()
    pcd.points = o3d.utility.Vector3dVector(np.stack([x, y, z], axis=1).astype(np.float64))
    pcd.colors = o3d.utility.Vector3dVector(colors.astype(np.float64))

    print("\nControls:  drag=rotate  scroll=zoom  shift+drag=pan  q/ESC=quit\n")

    vis = o3d.visualization.Visualizer()
    vis.create_window(window_name=f"Cave Map — {os.path.basename(ply_path)}", width=1280, height=800)
    vis.add_geometry(pcd)

    # Dark background like the reference image
    opt = vis.get_render_option()
    opt.background_color = np.array([0.05, 0.05, 0.05])
    opt.point_size = 2.0

    vis.run()
    vis.destroy_window()

else:
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D  # noqa: F401

    # Matplotlib 3D is slow for large clouds — cap at 100k
    CAP = 100_000
    if len(x) > CAP:
        print(f"  Matplotlib cap: showing {CAP:,} of {len(x):,} points (use open3d for full cloud)")
        idx = np.random.choice(len(x), CAP, replace=False)
        x, y, z, colors = x[idx], y[idx], z[idx], colors[idx]

    fig = plt.figure(figsize=(14, 9), facecolor="#0d0d0d")
    ax = fig.add_subplot(111, projection="3d", facecolor="#0d0d0d")
    ax.scatter(x, y, z, c=colors, s=0.5, linewidths=0)

    ax.set_xlabel("X (m)", color="white")
    ax.set_ylabel("Y (m)", color="white")
    ax.set_zlabel("Z (m)", color="white")
    ax.tick_params(colors="white")
    ax.set_title(os.path.basename(ply_path), color="white", pad=10)
    for pane in [ax.xaxis.pane, ax.yaxis.pane, ax.zaxis.pane]:
        pane.fill = False
    ax.set_aspect("equal", adjustable="box")

    print("\nDrag to rotate, scroll to zoom. Close window to exit.\n")
    plt.tight_layout()
    plt.show()
