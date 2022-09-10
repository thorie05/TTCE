import ttce
import pygame
import json
from screeninfo import get_monitors
from draw import draw
from events import events

# get the monitor dimensions
monitor = get_monitors()[0]
monitor_resolution = (monitor.width, monitor.height)
min_length = min(monitor_resolution)

# load the style settings
with open("style_settings.json", "r") as file:
    style_settings = json.load(file)

# calculate window width and height
width = round(min_length * style_settings["window_size"]["width_ratio"])
height = round(min_length * style_settings["window_size"]["height_ratio"])
if style_settings["window_size"]["use_absolute_values"]:
    width = style_settings["window_size"]["width"]
    height = style_settings["window_size"]["height"]


# initialize the pygame setup
pygame.init()
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Chess")


def get_color(draw_board, pos):
    # returns the color of a piece on the board

    if draw_board[pos[0]][pos[1]] == ".": # empty square
        return None
    if draw_board[pos[0]][pos[1]].isupper(): # white is uppercase
        return "w"
    return "b" # black is lowercase


def main():
    # main function to start everything

    board = ttce.Chessboard()
    player_color = "w"
    active_square = None

    # main loop
    while True:
        draw_board, turn, castling_rights, en_passant_square, \
            half_move_clock, full_move_number = board.get_board()
        event = events(player_color, turn)

        # if the player clicked outside the chessboard deactivate active square
        if event[0] == 1:
            active_square = None

        # if the player clicked inside the chessboard and it's the players turn
        elif event[0] == 2 and turn == player_color:
            pos = event[1]

            if active_square:
                if get_color(draw_board, pos) == player_color \
                    and pos != active_square:
                    active_square = pos
                else:
                    board.make_move(active_square, pos, change_turn=False)
                    active_square = None

            # if the player clicks one of his own pieces make the square active
            elif get_color(draw_board, pos) == player_color:
                active_square = pos


        # get the possible moves for the piece on the active square
        possible_moves = []

        # draw everything on the screen
        draw(screen, player_color, draw_board, active_square, possible_moves, 
            turn)


if __name__ == "__main__":
    main()
