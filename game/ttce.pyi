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