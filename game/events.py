import pygame
import math
import sys
import draw_variables


def events(perspective):
    """Handles the events"""

    absolute_tile_width, start_x_board, start_y_board, _, _, _, _, _ = \
        draw_variables.get_draw_variables()

    pos = None

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

        elif event.type == pygame.VIDEORESIZE:
            return "resized", None

        if event.type == pygame.MOUSEBUTTONUP: # left mouse button clicked
            if event.button == 1:
                # calculate tile clicked by the mouse
                pos = pygame.mouse.get_pos()
                pos = (math.floor((pos[0] - start_x_board) \
                    / absolute_tile_width), math.floor((pos[1] \
                    - start_y_board) / absolute_tile_width))

                # if clicked outisde of the board
                if pos[0] < 0 or pos[0] > 7 or pos[1] < 0 or pos[1] > 7:
                    pos = (-1, -1) 
                else: # adjust for perspective
                    if perspective == "w":
                        pos = (pos[0], 7 - pos[1])
                    else:
                        pos = (7 - pos[0], pos[1])
                return "click", pos

    return None, None

