from typing import Optional, List, Tuple

class Chessboard:
    """The Chessboard class"""

    def __init__(self, fen: Optional[str] = None) -> None:
        """Initialize board using FEN-String"""
        ...

    def get_status() -> Tuple[List[str], str, bool, bool, bool, bool, int, int, 
        int]:
        "Returns the current status of the board"
        ...

    def push_move(start_square: Tuple[int, int], end_square: Tuple[int, int]) -> \
        None:
        """Moves a piece on the board"""
        ...

    def get_pseudo_legal_moves() -> Tuple[Tuple[int, int], Tuple[int, int], 
        str]:
        """Returns all pseudo legal moves"""
        ...