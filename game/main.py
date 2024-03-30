import ttce
import pygame
from draw import draw
from events import events

pygame.init()


def main():
    """Main function"""

    board = ttce.Chessboard()

    active_square = None

    while True:
        board_status = board.get_status()
        draw_board = board_status[0]
        turn = board_status[1]

        if event := events():
            if event == (-1, -1):
                active_square = None
            else:
                active_square = event

        draw(draw_board, active_square, turn)


if __name__ == "__main__":
    main()
