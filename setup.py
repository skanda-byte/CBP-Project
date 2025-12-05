from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "lru_cache",
        ["bindings.cpp"],
    ),
]

setup(
    name="lru_cache",
    version="0.0.0",
    description="pybind11 LRUCache binding",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
