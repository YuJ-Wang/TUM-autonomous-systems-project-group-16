from setuptools import find_packages
from setuptools import setup

setup(
    name='statemachine_pkg',
    version='0.0.0',
    packages=find_packages(
        include=('statemachine_pkg', 'statemachine_pkg.*')),
)
