# generated from rosidl_generator_py/resource/_idl.py.em
# with input from utils:msg/GlobalMap.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

# Member 'occupied_ix'
# Member 'occupied_iy'
# Member 'occupied_iz'
# Member 'free_ix'
# Member 'free_iy'
# Member 'free_iz'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GlobalMap(type):
    """Metaclass of message 'GlobalMap'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('utils')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'utils.msg.GlobalMap')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__global_map
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__global_map
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__global_map
            cls._TYPE_SUPPORT = module.type_support_msg__msg__global_map
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__global_map

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GlobalMap(metaclass=Metaclass_GlobalMap):
    """Message class 'GlobalMap'."""

    __slots__ = [
        '_header',
        '_map_type',
        '_frame_id',
        '_resolution',
        '_occupied_voxels',
        '_free_voxels',
        '_unknown_voxels',
        '_explored_volume_m3',
        '_storage_path',
        '_valid',
        '_occupied_ix',
        '_occupied_iy',
        '_occupied_iz',
        '_free_ix',
        '_free_iy',
        '_free_iz',
        '_frontier_goal',
        '_frontier_goal_valid',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'map_type': 'string',
        'frame_id': 'string',
        'resolution': 'float',
        'occupied_voxels': 'uint32',
        'free_voxels': 'uint32',
        'unknown_voxels': 'uint32',
        'explored_volume_m3': 'float',
        'storage_path': 'string',
        'valid': 'boolean',
        'occupied_ix': 'sequence<int32>',
        'occupied_iy': 'sequence<int32>',
        'occupied_iz': 'sequence<int32>',
        'free_ix': 'sequence<int32>',
        'free_iy': 'sequence<int32>',
        'free_iz': 'sequence<int32>',
        'frontier_goal': 'geometry_msgs/Point',
        'frontier_goal_valid': 'boolean',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.map_type = kwargs.get('map_type', str())
        self.frame_id = kwargs.get('frame_id', str())
        self.resolution = kwargs.get('resolution', float())
        self.occupied_voxels = kwargs.get('occupied_voxels', int())
        self.free_voxels = kwargs.get('free_voxels', int())
        self.unknown_voxels = kwargs.get('unknown_voxels', int())
        self.explored_volume_m3 = kwargs.get('explored_volume_m3', float())
        self.storage_path = kwargs.get('storage_path', str())
        self.valid = kwargs.get('valid', bool())
        self.occupied_ix = array.array('i', kwargs.get('occupied_ix', []))
        self.occupied_iy = array.array('i', kwargs.get('occupied_iy', []))
        self.occupied_iz = array.array('i', kwargs.get('occupied_iz', []))
        self.free_ix = array.array('i', kwargs.get('free_ix', []))
        self.free_iy = array.array('i', kwargs.get('free_iy', []))
        self.free_iz = array.array('i', kwargs.get('free_iz', []))
        from geometry_msgs.msg import Point
        self.frontier_goal = kwargs.get('frontier_goal', Point())
        self.frontier_goal_valid = kwargs.get('frontier_goal_valid', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.map_type != other.map_type:
            return False
        if self.frame_id != other.frame_id:
            return False
        if self.resolution != other.resolution:
            return False
        if self.occupied_voxels != other.occupied_voxels:
            return False
        if self.free_voxels != other.free_voxels:
            return False
        if self.unknown_voxels != other.unknown_voxels:
            return False
        if self.explored_volume_m3 != other.explored_volume_m3:
            return False
        if self.storage_path != other.storage_path:
            return False
        if self.valid != other.valid:
            return False
        if self.occupied_ix != other.occupied_ix:
            return False
        if self.occupied_iy != other.occupied_iy:
            return False
        if self.occupied_iz != other.occupied_iz:
            return False
        if self.free_ix != other.free_ix:
            return False
        if self.free_iy != other.free_iy:
            return False
        if self.free_iz != other.free_iz:
            return False
        if self.frontier_goal != other.frontier_goal:
            return False
        if self.frontier_goal_valid != other.frontier_goal_valid:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if self._check_fields:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def map_type(self):
        """Message field 'map_type'."""
        return self._map_type

    @map_type.setter
    def map_type(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'map_type' field must be of type 'str'"
        self._map_type = value

    @builtins.property
    def frame_id(self):
        """Message field 'frame_id'."""
        return self._frame_id

    @frame_id.setter
    def frame_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'frame_id' field must be of type 'str'"
        self._frame_id = value

    @builtins.property
    def resolution(self):
        """Message field 'resolution'."""
        return self._resolution

    @resolution.setter
    def resolution(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'resolution' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'resolution' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._resolution = value

    @builtins.property
    def occupied_voxels(self):
        """Message field 'occupied_voxels'."""
        return self._occupied_voxels

    @occupied_voxels.setter
    def occupied_voxels(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'occupied_voxels' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'occupied_voxels' field must be an unsigned integer in [0, 4294967295]"
        self._occupied_voxels = value

    @builtins.property
    def free_voxels(self):
        """Message field 'free_voxels'."""
        return self._free_voxels

    @free_voxels.setter
    def free_voxels(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'free_voxels' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'free_voxels' field must be an unsigned integer in [0, 4294967295]"
        self._free_voxels = value

    @builtins.property
    def unknown_voxels(self):
        """Message field 'unknown_voxels'."""
        return self._unknown_voxels

    @unknown_voxels.setter
    def unknown_voxels(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'unknown_voxels' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'unknown_voxels' field must be an unsigned integer in [0, 4294967295]"
        self._unknown_voxels = value

    @builtins.property
    def explored_volume_m3(self):
        """Message field 'explored_volume_m3'."""
        return self._explored_volume_m3

    @explored_volume_m3.setter
    def explored_volume_m3(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'explored_volume_m3' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'explored_volume_m3' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._explored_volume_m3 = value

    @builtins.property
    def storage_path(self):
        """Message field 'storage_path'."""
        return self._storage_path

    @storage_path.setter
    def storage_path(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'storage_path' field must be of type 'str'"
        self._storage_path = value

    @builtins.property
    def valid(self):
        """Message field 'valid'."""
        return self._valid

    @valid.setter
    def valid(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'valid' field must be of type 'bool'"
        self._valid = value

    @builtins.property
    def occupied_ix(self):
        """Message field 'occupied_ix'."""
        return self._occupied_ix

    @occupied_ix.setter
    def occupied_ix(self, value):
        if self._check_fields:
            if isinstance(value, array.array):
                assert value.typecode == 'i', \
                    "The 'occupied_ix' array.array() must have the type code of 'i'"
                self._occupied_ix = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'occupied_ix' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._occupied_ix = array.array('i', value)

    @builtins.property
    def occupied_iy(self):
        """Message field 'occupied_iy'."""
        return self._occupied_iy

    @occupied_iy.setter
    def occupied_iy(self, value):
        if self._check_fields:
            if isinstance(value, array.array):
                assert value.typecode == 'i', \
                    "The 'occupied_iy' array.array() must have the type code of 'i'"
                self._occupied_iy = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'occupied_iy' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._occupied_iy = array.array('i', value)

    @builtins.property
    def occupied_iz(self):
        """Message field 'occupied_iz'."""
        return self._occupied_iz

    @occupied_iz.setter
    def occupied_iz(self, value):
        if self._check_fields:
            if isinstance(value, array.array):
                assert value.typecode == 'i', \
                    "The 'occupied_iz' array.array() must have the type code of 'i'"
                self._occupied_iz = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'occupied_iz' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._occupied_iz = array.array('i', value)

    @builtins.property
    def free_ix(self):
        """Message field 'free_ix'."""
        return self._free_ix

    @free_ix.setter
    def free_ix(self, value):
        if self._check_fields:
            if isinstance(value, array.array):
                assert value.typecode == 'i', \
                    "The 'free_ix' array.array() must have the type code of 'i'"
                self._free_ix = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'free_ix' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._free_ix = array.array('i', value)

    @builtins.property
    def free_iy(self):
        """Message field 'free_iy'."""
        return self._free_iy

    @free_iy.setter
    def free_iy(self, value):
        if self._check_fields:
            if isinstance(value, array.array):
                assert value.typecode == 'i', \
                    "The 'free_iy' array.array() must have the type code of 'i'"
                self._free_iy = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'free_iy' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._free_iy = array.array('i', value)

    @builtins.property
    def free_iz(self):
        """Message field 'free_iz'."""
        return self._free_iz

    @free_iz.setter
    def free_iz(self, value):
        if self._check_fields:
            if isinstance(value, array.array):
                assert value.typecode == 'i', \
                    "The 'free_iz' array.array() must have the type code of 'i'"
                self._free_iz = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'free_iz' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._free_iz = array.array('i', value)

    @builtins.property
    def frontier_goal(self):
        """Message field 'frontier_goal'."""
        return self._frontier_goal

    @frontier_goal.setter
    def frontier_goal(self, value):
        if self._check_fields:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'frontier_goal' field must be a sub message of type 'Point'"
        self._frontier_goal = value

    @builtins.property
    def frontier_goal_valid(self):
        """Message field 'frontier_goal_valid'."""
        return self._frontier_goal_valid

    @frontier_goal_valid.setter
    def frontier_goal_valid(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'frontier_goal_valid' field must be of type 'bool'"
        self._frontier_goal_valid = value
