import ttce
import pygame
from draw import draw
from events import events

pygame.init()


def main():
    """Main function"""

    board = ttce.Chessboard()

    active_square = None
    perspective = "w"

    while True:
        # get board status
        board_status = board.get_status()
        draw_board = board_status[0]

        if event := events(perspective):
            # if clicked outside of the board remove active square
            if event == (-1, -1):
                active_square = None
            else:
                # if already active square
                if active_square:
                    active_piece = \
                        draw_board[active_square[0]][active_square[1]]
                    new_piece = draw_board[event[0]][event[1]]

                    active_piece_color = "w" if active_piece.isupper() else "b"
                    new_piece_color = "w" if new_piece.isupper() else "b"
                    if new_piece == " ":
                        new_piece_color = " "

                    # if clicked on enemy piece or empty square push move
                    if active_piece_color != new_piece_color: 
                        board.push_move(active_square, event)
                        active_square = None

                    # if clicked on friendly piece
                    if active_piece_color == new_piece_color:
                        # if other piece make new active square
                        if active_square != event:
                            active_square = event
                        # if same piece remove active square
                        else:
                            active_square = None

                # if no active square make new active square
                else:
                    active_square = event

        # calculate legal moves for active square for visualisation
        legal_active_square_moves = []
        if active_square:
            legal_moves = board.get_pseudo_legal_moves()
            legal_active_square_moves = [move[1] for move in legal_moves \
                if move[0] == active_square]

        draw(draw_board, active_square, legal_active_square_moves, perspective)


if __name__ == "__main__":
    main()
