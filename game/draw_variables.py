import pygame
import json

# global draw variables relevant for the draw function
absolute_tile_width = None
start_x_board = None
start_y_board = None
absolute_board_border_width = None
absolute_active_square_border_width = None
absolute_legal_move_circle_radius = None
absolute_piece_width = None
piece_images = {}


def update_draw_variables(new_height, new_width):
    """updates the global draw variables"""

    global absolute_tile_width, start_x_board, start_y_board, \
        absolute_board_border_width, absolute_active_square_border_width, \
        absolute_legal_move_circle_radius, absolute_piece_width, piece_images

    absolute_tile_width = round(new_height * style_settings["tile_width"])
    start_x_board = round((new_width - absolute_tile_width * 8) / 2)
    start_y_board = round((new_height - absolute_tile_width * 8) / 2)
    absolute_board_border_width = round(new_height 
        * style_settings["board_border_width"])
    absolute_active_square_border_width = round(absolute_tile_width \
        * style_settings["active_square_border_width"])
    absolute_legal_move_circle_radius = round(absolute_tile_width \
        * style_settings["legal_move_circle_radius"])

    absolute_piece_width = round(absolute_tile_width \
        * style_settings["pieces"]["relative_piece_width"])

    # scale piece images to correct size
    for k, v in original_piece_images.items():
        piece_images[k] = pygame.transform.scale(v, (absolute_piece_width, 
            absolute_piece_width))


def get_draw_variables():
    """returns the global draw variables"""

    return [absolute_tile_width, start_x_board, start_y_board, 
        absolute_board_border_width, absolute_active_square_border_width,
        absolute_legal_move_circle_radius, absolute_piece_width, piece_images]


# load style settings json
with open("game/style_settings.json") as file:
    style_settings = json.load(file)
colors = style_settings["colors"]

piece_style = style_settings["pieces"]["piece_style"]

# load pieces
original_piece_images = {
    "P": pygame.image.load(f"game/img/{piece_style}/wP.svg"),
    "N": pygame.image.load(f"game/img/{piece_style}/wN.svg"),
    "B": pygame.image.load(f"game/img/{piece_style}/wB.svg"),
    "R": pygame.image.load(f"game/img/{piece_style}/wR.svg"),
    "Q": pygame.image.load(f"game/img/{piece_style}/wQ.svg"),
    "K": pygame.image.load(f"game/img/{piece_style}/wK.svg"),
    "p": pygame.image.load(f"game/img/{piece_style}/bP.svg"),
    "n": pygame.image.load(f"game/img/{piece_style}/bN.svg"),
    "b": pygame.image.load(f"game/img/{piece_style}/bB.svg"),
    "r": pygame.image.load(f"game/img/{piece_style}/bR.svg"),
    "q": pygame.image.load(f"game/img/{piece_style}/bQ.svg"),
    "k": pygame.image.load(f"game/img/{piece_style}/bK.svg"),
}

update_draw_variables(0, 0)

