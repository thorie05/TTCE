import pygame
import json
from screeninfo import get_monitors

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

# calculate paddings and cell and piece dimensions
bottom_padding = round(height * style_settings["bottom_padding_ratio"])
cell_size = round((height - 2 * bottom_padding) / 8)
piece_size = round(style_settings["pieces"]["piece_size_ratio"] * cell_size)
active_square_border_size = round(cell_size \
    * style_settings["active_square_border_size_ratio"])
board_with_border_size = round(8 * cell_size \
    * style_settings["board_border_size_ratio"])
possible_move_circle_radius = cell_size \
    * style_settings["possible_move_circle_radius_ratio"]
left_padding = round(width / 2 - 4 * cell_size)

colors = style_settings["colors"]
piece_style = style_settings["pieces"]["piece_style"]

# map the piece images to its corresponding number on the board
piece_images = {
    "P": pygame.image.load(f"img/{piece_style}/wP.png"),
    "N": pygame.image.load(f"img/{piece_style}/wN.png"),
    "B": pygame.image.load(f"img/{piece_style}/wB.png"),
    "R": pygame.image.load(f"img/{piece_style}/wR.png"),
    "Q": pygame.image.load(f"img/{piece_style}/wQ.png"),
    "K": pygame.image.load(f"img/{piece_style}/wK.png"),
    "p": pygame.image.load(f"img/{piece_style}/bP.png"),
    "n": pygame.image.load(f"img/{piece_style}/bN.png"),
    "b": pygame.image.load(f"img/{piece_style}/bB.png"),
    "r": pygame.image.load(f"img/{piece_style}/bR.png"),
    "q": pygame.image.load(f"img/{piece_style}/bQ.png"),
    "k": pygame.image.load(f"img/{piece_style}/bK.png"),
}

# scale the piece images to the right size
for k, v in piece_images.items():
    piece_images[k] = pygame.transform.scale(v, (piece_size, piece_size))


def draw(screen, perspective, board, active_square, possible_moves, turn):
    """Draws everything on the screen"""

    # turn the board by 180 degrees if the perspective is from black
    original_board = [e.copy() for e in board]
    rotated_board = board
    if perspective == "b":
        for x in range(8):
            for y in range(8):
                rotated_board[x][7 - y] = original_board[7 - x][y]

    screen.fill(colors["white"])

    # draw the chessboard border
    pygame.draw.rect(screen, colors["dark_brown2"], (left_padding \
        - round((board_with_border_size - 8 * cell_size) / 2), 
        bottom_padding - round((board_with_border_size - 8 * cell_size) / 2) \
        - round(height * 0.002), board_with_border_size, 
        board_with_border_size))

    # draw the squares and the pieces
    for x in range(8):
        for y in range(8):
            if (x + y) % 2 == 1: # draw a white square
                pygame.draw.rect(screen, colors["light_brown"], 
                    (left_padding + x * cell_size, height - bottom_padding \
                    - cell_size - y * cell_size, cell_size, cell_size))
            else: # draw a black square
                pygame.draw.rect(screen, colors["dark_brown"], 
                    (left_padding + x * cell_size, height - bottom_padding \
                    - cell_size - y * cell_size, cell_size, cell_size))

            # draw the pieces
            if rotated_board[x][y] != ".":
                screen.blit(piece_images[rotated_board[x][y]], (left_padding \
                    + x * cell_size + round((cell_size - piece_size) / 2), 
                    height - bottom_padding - cell_size - y * cell_size \
                    + round((cell_size - piece_size) / 2)))

    if active_square:
        if perspective == "w":
            active_square = (active_square[0], 7 - active_square[1])
        else:
            active_square = (7 - active_square[0], active_square[1])

        # highight the active square
        pygame.draw.rect(screen, colors["white"], (left_padding + cell_size \
            * active_square[0], bottom_padding - active_square_border_size \
            + cell_size * active_square[1], cell_size, 
            active_square_border_size))
        pygame.draw.rect(screen, colors["white"], (left_padding + cell_size \
            * active_square[0], bottom_padding - 2 \
            * active_square_border_size + cell_size * (active_square[1] + 1),
            cell_size, active_square_border_size))
        pygame.draw.rect(screen, colors["white"], (left_padding + cell_size \
            * active_square[0], bottom_padding - active_square_border_size \
            + cell_size * active_square[1], active_square_border_size, 
            cell_size))
        pygame.draw.rect(screen, colors["white"], (left_padding \
            - active_square_border_size + cell_size * (active_square[0] + 1),
            bottom_padding - active_square_border_size + cell_size \
            * active_square[1], active_square_border_size, cell_size))

        # show all possible moves for piece on the active square
        for _, move in possible_moves:
            if perspective == "w":
                draw_move = (move[0], 7 - move[1])
            else:
                draw_move = (7 - move[0], move[1])

            # if the move captures a piece
            if original_board[move[0]][move[1]]:
                pygame.draw.circle(screen, colors["gray"], (left_padding \
                    + round(cell_size / 2) + draw_move[0] * cell_size, 
                    bottom_padding + round(cell_size / 2) + draw_move[1] \
                    * cell_size), possible_move_circle_radius)
            # if the move is on an empty square
            else:
                pygame.draw.circle(screen, colors["white"], (left_padding \
                    + round(cell_size / 2) + draw_move[0] * cell_size, 
                    bottom_padding + round(cell_size / 2) + draw_move[1] \
                    * cell_size), possible_move_circle_radius)

    pygame.display.flip()
