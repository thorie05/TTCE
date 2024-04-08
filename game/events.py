import pygame
import math
import sys
from dataclasses import dataclass
from typing import Tuple
from display_settings import ds

@dataclass
class GameEvent():
    """
    Dataclass containing information about an event in the game.

    Attributes
    ----------
        event_type : str
            event type of the event (click or resized)
        clicked_pos : Tuple[int, int]
            position of the click if clicked else None

    Methods
    -------
        None
    """

    event_type: str
    clicked_pos: Tuple[int, int] = None


def events(perspective):
    """
    Handles the events.

    Parameters
    ----------
        perspective : str
            perspective of the player (w or b)

    Returns
    -------
        event : GameEvent
            GameEvent object containing information about the event
    """

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit() # exit the game

        # window resized
        elif ds.resizable and event.type == pygame.VIDEORESIZE:
            return GameEvent(event_type="resized")

        # mouse clicked
        if event.type == pygame.MOUSEBUTTONUP:
            # left mouse button clicked
            if event.button == 1:
                # calculate coordinates of the clicked square
                clicked_pos = pygame.mouse.get_pos()
                clicked_pos = (math.floor((clicked_pos[0] - ds.start_x_board) \
                    / ds.tile_width), math.floor((clicked_pos[1] \
                    - ds.start_y_board) / ds.tile_width))

                # if clicked outisde of the board
                if clicked_pos[0] < 0 or clicked_pos[0] > 7 \
                    or clicked_pos[1] < 0 or clicked_pos[1] > 7:
                    clicked_pos = None 
                else:
                    # account for perspective
                    if perspective == "w":
                        clicked_pos = (clicked_pos[0], 7 - clicked_pos[1])
                    else:
                        clicked_pos = (7 - clicked_pos[0], clicked_pos[1])

                return GameEvent(event_type="click", clicked_pos=clicked_pos)

    return GameEvent("none")
