#include <pybind11/pybind11.h>
#include "LRU_CPP.hpp"
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>



namespace py = pybind11;

PYBIND11_MODULE(lru_cache, m) {
    py::class_<LRUCache>(m, "LRUCache")
        .def(py::init<int>())
        .def("get", &LRUCache::get)
        .def("put", &LRUCache::put)
        .def("get_all", &LRUCache::get_all);

}
