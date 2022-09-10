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

        .def("__str__", &Chessboard::toString, "Converts the current board position into a readable string.")

        .def("get_board", &Chessboard::getBoard, "Returns the current board position")

        .def("get_fen", &Chessboard::getFen, "Returns the FEN of the current board position.")

        .def("make_move", py::overload_cast<int, int, const std::string&, bool>(&Chessboard::makeMove), 
            "Make a move on the board from the start square to the end square using bitboard square numbering.", 
            py::arg("start_square"), py::arg("end_square"), py::arg("promotion") = "", py::arg("change_turn") = true)

        .def("make_move", py::overload_cast<
            const std::tuple<int,int>&, const std::tuple<int,int>&, const std::string&, bool>(&Chessboard::makeMove), 
            "Make a move on the board from the start square to the end square using the square coordinates.", 
            py::arg("start_square"), py::arg("end_square"), py::arg("promotion") = "", py::arg("change_turn") = true)

        .def("make_move", py::overload_cast<
            const std::string&, const std::string&, const std::string&, bool>(&Chessboard::makeMove), 
            "Make a move on the board from the start square to the end square using algebraic notation.", 
            py::arg("start_square"), py::arg("end_square"), py::arg("promotion") = "", py::arg("change_turn") = true)
        ;
}
