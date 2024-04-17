from typing import Optional, List, Tuple

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

    def get_board_info() -> Tuple[List[str], str, bool, bool, bool, bool, int,
        int, int]:
        """
        Returns the current board state, like the pieces or castling rights.

        Parameters
        ----------
            None

        Returns
        -------
            boardStatus object (not implemented yet)
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

    def get_pseudo_legal_moves() -> \
        List[Tuple[Tuple[int, int], Tuple[int, int], str]]:
        """
        Returns all pseudo-legal moves for the current position.

        Parameters
        ----------
            None

        Returns
        -------
            pseudo_legal_moves : List[Tuple[int, int], Tuple[int, int], str]
                list of all pseudo legal moves for the current position
        """
        ...