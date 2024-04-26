import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide" # hide pygame welcome message

import ttce
import pygame
from draw import draw
from events import events
from display_settings import ds

pygame.init()


def main():
    """
    The main function running the game loop.

    Parameters
    ----------
        None

    Returns
    -------
        None
    """

    # initialize chessboard class from the ttce module
    chessboard = ttce.Chessboard()

    active_square = None # square currently clicked by the player
    perspective = "w" # perspective of the drawn chessboard (w or b)

    # main loop
    while True:
        # get board status
        board_status = chessboard.get_board_info()
        board = board_status[0]

        event = events(perspective)
        # if clicked
        if event.event_type == "click":
            clicked_pos = event.clicked_pos

            # if clicked outside of the board remove active square
            if clicked_pos:
                # if already active square
                if active_square:
                    active_piece = board[active_square[0]][active_square[1]]
                    new_piece = board[clicked_pos[0]][clicked_pos[1]]

                    active_piece_color = "w" if active_piece.isupper() else "b"
                    new_piece_color = "w" if new_piece.isupper() else "b"
                    if new_piece == " ":
                        new_piece_color = " "

                    # if clicked on enemy piece or empty square push move
                    if active_piece_color != new_piece_color: 
                        chessboard.move(active_square, clicked_pos)
                        active_square = None

                    # if clicked on friendly piece
                    if active_piece_color == new_piece_color:
                        # if other piece make new active square
                        if active_square != clicked_pos:
                            active_square = clicked_pos
                        # if same piece remove active square
                        else:
                            active_square = None

                # if no active square make new active square
                elif board[clicked_pos[0]][clicked_pos[1]] != " ":
                    active_square = clicked_pos
            else: # if clicked outside of the board remove active square
                active_square = None
        # if resized window
        elif event.event_type == "resized":
            new_width, new_height = pygame.display.get_surface().get_size()
            ds.update(new_width, new_height)

        # calculate legal moves for active square for visualisation
        legal_active_square_moves = []
        if active_square:
            legal_moves = chessboard.get_legal_moves()
            legal_active_square_moves = [move[1] for move in legal_moves \
                if move[0] == active_square]

        draw(board, active_square, legal_active_square_moves, perspective)


if __name__ == "__main__":
    main()
