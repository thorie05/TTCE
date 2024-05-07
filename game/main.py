import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide" # hide pygame welcome message

import ttce
import pygame

pygame.init()
pygame.font.init()

from draw import draw
from events import events
from display_settings import ds
from promotion_popup import PromotionPopup


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
    fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1"
    chessboard = ttce.Chessboard(fen)

    active_square = None # square currently clicked by the player
    perspective = "b" # perspective of the drawn chessboard (w or b)

    # main loop
    while True:
        # get board status
        board_info = chessboard.get_board_info()

        # calculate legal moves for active square for visualisation
        legal_active_square_moves = []
        if active_square:
            legal_moves = chessboard.get_legal_moves()
            legal_active_square_moves = [move[1] for move in legal_moves \
                if move[0] == active_square]

        event = events(perspective)
        # if clicked
        if event.event_type == "click":
            clicked_pos = event.clicked_pos

            # if clicked outside of the board remove active square
            if clicked_pos:
                # if already active square
                if active_square:
                    active_piece = \
                        board_info.board[active_square[0]][active_square[1]]
                    new_piece = board_info.board[clicked_pos[0]][clicked_pos[1]]

                    active_piece_color = "w" if active_piece.isupper() else "b"
                    new_piece_color = "w" if new_piece.isupper() else "b"
                    if new_piece == " ":
                        new_piece_color = " "

                    # if clicked on enemy piece or empty square push move
                    if active_piece_color != new_piece_color: 
                        if active_piece == "P" and clicked_pos[1] == 7:
                            # white promoting
                            promo = PromotionPopup("w", board_info.board,
                                active_square, legal_active_square_moves,
                                perspective).run()
                            chessboard.move(active_square, clicked_pos, promo)
                        elif active_piece == "p" and clicked_pos[1] == 0:
                            # black promoting
                            promo = PromotionPopup("b", board_info.board,
                                active_square, legal_active_square_moves,
                                perspective).run()
                            chessboard.move(active_square, clicked_pos, promo)
                        else:
                            # no promtion
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
                elif board_info.board[clicked_pos[0]][clicked_pos[1]] != " ":
                    active_square = clicked_pos
            else: # if clicked outside of the board remove active square
                active_square = None

        # if resized window
        elif event.event_type == "resized":
            new_width, new_height = pygame.display.get_surface().get_size()
            ds.update(new_width, new_height)

        # if key pressed
        elif event.event_type == "keypress":
            if event.pressed_keys[pygame.K_LCTRL] \
                and event.pressed_keys[pygame.K_z]:
                chessboard.unmake_move()

        draw(board_info.board, active_square, legal_active_square_moves,
            perspective)


if __name__ == "__main__":
    main()
