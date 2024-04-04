import ttce
import pygame
from draw import draw
from events import events
import draw_variables

pygame.init()


def main():
    """Main function"""

    chessboard = ttce.Chessboard()

    active_square = None
    perspective = "w"

    while True:
        # get board status
        board_status = chessboard.get_status()
        board = board_status[0]

        event = events(perspective)
        if event[0] == "click":
            click_pos = event[1]

            # if clicked outside of the board remove active square
            if click_pos == (-1, -1):
                active_square = None
            else:
                # if already active square
                if active_square:
                    active_piece = \
                        board[active_square[0]][active_square[1]]
                    new_piece = board[click_pos[0]][click_pos[1]]

                    active_piece_color = "w" if active_piece.isupper() else "b"
                    new_piece_color = "w" if new_piece.isupper() else "b"
                    if new_piece == " ":
                        new_piece_color = " "

                    # if clicked on enemy piece or empty square push move
                    if active_piece_color != new_piece_color: 
                        chessboard.push_move(active_square, click_pos)
                        active_square = None

                    # if clicked on friendly piece
                    if active_piece_color == new_piece_color:
                        # if other piece make new active square
                        if active_square != click_pos:
                            active_square = click_pos
                        # if same piece remove active square
                        else:
                            active_square = None

                # if no active square make new active square
                elif board[click_pos[0]][click_pos[1]] != " ":
                    active_square = click_pos
        elif event[0] == "resized":
            new_width, new_height = pygame.display.get_surface().get_size()
            draw_variables.update_draw_variables(new_height, new_width)

        # calculate legal moves for active square for visualisation
        legal_active_square_moves = []
        if active_square:
            legal_moves = chessboard.get_pseudo_legal_moves()
            legal_active_square_moves = [move[1] for move in legal_moves \
                if move[0] == active_square]

        draw(board, active_square, legal_active_square_moves, perspective)


if __name__ == "__main__":
    main()
