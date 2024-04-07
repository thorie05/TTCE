#include "chessboard.hpp"
#include <string>
#include <tuple>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(ttce, handle) {
    handle.doc() = "Thomas the Chess Engine";

    py::class_<Chessboard>(handle, "Chessboard")

        .def(py::init<const std::string&>(),
            py::arg("fen") = DEFAULT_FEN)

        .def("get_status", &Chessboard::getStatus)

        .def("push_move", py::overload_cast<std::tuple<int,int>, 
            std::tuple<int,int>, char>(&Chessboard::pushMove), 
            py::arg("start_square"), py::arg("end_square"), 
            py::arg("promotion_piece") = 'q')

        .def("get_pseudo_legal_moves", &Chessboard::getPseudoLegalMovesPy)
    ;
}