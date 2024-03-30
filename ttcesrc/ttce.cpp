#include "chessboard.hpp"
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(ttce, handle) {
    handle.doc() = "Thomas the Chess Engine";

    py::class_<Chessboard>(handle, "Chessboard")

        .def(py::init<const std::string&>(),
            py::arg("fen") = defaultFen)

        .def("get_status", &Chessboard::getStatus)
    ;
}