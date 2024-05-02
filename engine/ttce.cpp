#include "chessboard.hpp"
#include "constants.hpp"
#include <string>
#include <tuple>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(ttce, handle) {
    handle.doc() = "Thomas the Chess Engine";

    py::class_<BoardInfo>(handle, "BoardInfo")

        .def_readwrite("board", &BoardInfo::board)

        .def_readwrite("turn", &BoardInfo::turn)
    ;

    py::class_<Chessboard>(handle, "Chessboard")

        .def(py::init<const std::string&>(), py::arg("fen") = DEFAULT_FEN)

        .def("get_pseudo_legal_moves", &Chessboard::getPseudoLegalMovesPy)

        .def("get_legal_moves", &Chessboard::getLegalMovesPy)

        .def("move", py::overload_cast<const std::tuple<int,int>&,
            const std::tuple<int, int>&, char>(&Chessboard::movePy),
            py::arg("start_square"), py::arg("end_square"),
            py::arg("promotion_piece") = 'q')

        .def("unmake_move", &Chessboard::unmakeMove)

        .def("get_board_info", &Chessboard::getBoardInfoPy)
    ;
}