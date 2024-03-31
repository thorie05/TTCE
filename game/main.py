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
            if event == (-1, -1): # clicked outside of the board
                active_square = None
            else:
                if active_square: # if already active square move piece
                    if active_square != event: # if clicked on different square
                        board.push_move(active_square, event)
                    active_square = None
                else: # if no active square make new active square
                    active_square = event

        draw(draw_board, active_square, perspective)


if __name__ == "__main__":
    main()
