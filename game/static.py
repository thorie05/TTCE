import pygame
import json
from screeninfo import get_monitors

# get monitor height
monitor_height = 0
for m in get_monitors():
    monitor_height = max(monitor_height, m.height)

# load style settings json
with open("game/style_settings.json") as file:
    style_settings = json.load(file)
colors = style_settings["colors"]

if style_settings["window"]["use_absolute_values"]:
    width = style_settings["window"]["width"]
    height = style_settings["window"]["height"]
else:
    width = monitor_height * style_settings["window"]["relative_width"]
    height = monitor_height * style_settings["window"]["relative_height"]

absolute_tile_width = round(height * style_settings["tile_width"])
start_x_board = round((width - absolute_tile_width * 8) / 2)
start_y_board = round((height - absolute_tile_width * 8) / 2)
absolute_board_border_width = round(height 
    * style_settings["board_border_width"])
absolute_active_square_border_width = round(absolute_tile_width \
    * style_settings["active_square_border_width"])

piece_style = style_settings["pieces"]["piece_style"]
absolute_piece_width = round(absolute_tile_width \
    * style_settings["pieces"]["relative_piece_width"])

# load pieces
piece_images = {
    "P": pygame.image.load(f"game/img/{piece_style}/wP.png"),
    "N": pygame.image.load(f"game/img/{piece_style}/wN.png"),
    "B": pygame.image.load(f"game/img/{piece_style}/wB.png"),
    "R": pygame.image.load(f"game/img/{piece_style}/wR.png"),
    "Q": pygame.image.load(f"game/img/{piece_style}/wQ.png"),
    "K": pygame.image.load(f"game/img/{piece_style}/wK.png"),
    "p": pygame.image.load(f"game/img/{piece_style}/bP.png"),
    "n": pygame.image.load(f"game/img/{piece_style}/bN.png"),
    "b": pygame.image.load(f"game/img/{piece_style}/bB.png"),
    "r": pygame.image.load(f"game/img/{piece_style}/bR.png"),
    "q": pygame.image.load(f"game/img/{piece_style}/bQ.png"),
    "k": pygame.image.load(f"game/img/{piece_style}/bK.png"),
}

# scale piece images to correct size
for k, v in piece_images.items():
    piece_images[k] = pygame.transform.scale(v, (absolute_piece_width, 
        absolute_piece_width))
