from typing import Optional, List, Tuple


class BoardInfo:
    """
    A class that holds information about the current board state.

    Attributes
    ----------
        board : List[List[str]]
            current piece arrangement
        turn : str
            whose turn is it - w or b

    Methods
    -------
        None
    """

    board: List[List[str]]
    turn: str


class Chessboard:
    """
    The main class of the TTCE Chess Engine.

    Attributes
    ----------
        None

    Methods
    -------
        get_status():
            Returns the current board state, like the pieces or castling rights.
        push_move(start_square, end_square):
            Moves a piece on the board from start_square to end_square.
        get_pseudo_legal_moves():
            Returns all pseudo-legal moves for the current position.
    """

    def __init__(self, fen: Optional[str]) -> None:
        """
        Initializes the Chessboard class using the given FEN-string.

        Parameters
        ----------
            fen : str, optional
                fen string for setting up the board, default = starting position

        Returns
        -------
            None
        """
        ...

    def get_board_info() -> BoardInfo:
        """
        Returns the current state of the board using the BoardInfo class.

        Parameters
        ----------
            None

        Returns
        -------
            info : BoardInfo
        """
        ...

    def move(start_square: Tuple[int, int], end_square: Tuple[int, int], 
        promotion_piece: Optional[str]) -> None:
        """
        Moves a piece on the board from start_square to end_square.

        Parameters
        ----------
            start_square : Tuple[int, int]
                current coordinats of the piece to be moved
            end_square : Tuple[int, int]
                coordinates of the square the piece should be moved to
            promotion_piece : str, optional
                piece to be promoted to (q, r, b, n), default = q

        Returns
        -------
            None
        """
        ...

    def get_legal_moves() -> List[Tuple[Tuple[int, int], Tuple[int, int], str]]:
        """
        Returns all legal moves for the current position.

        Parameters
        ----------
            None

        Returns
        -------
            legal_moves : List[Tuple[int, int], Tuple[int, int], str]
                list of all legal moves for the current position
        """
        ...