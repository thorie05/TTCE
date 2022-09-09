#include "chessboard.hpp"

#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(ttce, handle) {
    py::class_<Chessboard>(handle, "Chessboard")
        .def(py::init<const std::string&>(), 
            "Initializes the board using the given FEN-String. If no string is passed the normal starting position is used.", 
            py::arg("inputFenString") = defaultFenString)
        .def("get_board", &Chessboard::getBoard, "Returns the current board position")
        .def("__str__", &Chessboard::toString, "Converts the current board position into a readable string.")
        .def("get_fen", &Chessboard::getFen, "Returns the FEN of the current board position.")
        ;
}
