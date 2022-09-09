import pygame
import json
import sys
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

# calculate paddings and cell dimensions
bottom_padding = round(height * style_settings["bottom_padding_ratio"])
cell_size = round((height - 2 * bottom_padding) / 8)
left_padding = round(width / 2 - 4 * cell_size)


def events(perspective, turn):
    """Handles the events"""

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

        # if the user clicks the window
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            pos = pygame.mouse.get_pos()

            # if the click is within the chessboard return the square position
            if pos[0] > left_padding and pos[0] < left_padding + 8 \
                * cell_size and pos[1] > bottom_padding and pos[1] \
                < bottom_padding + 8 * cell_size: 

                # calculate the square position
                square = ((pos[0] - left_padding) // cell_size, 
                    ((pos[1] - bottom_padding) // cell_size))

                if perspective == "w":
                    square = (square[0], 7 - square[1])
                else:
                    square = (7 - square[0], square[1])

                return (2, square) # return 2 and the square coordinates if 
                                   #the player clicked inside the chessboard

            return (1,) # return (1) if player clicked outside the chessboard
    return (0,) # return (0) if no event happened
