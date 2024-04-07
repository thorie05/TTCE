import pygame
import json


class DisplaySettings():
    def __init__(self):
        """
        Initializes the DisplaySettings class.

        Parameters
        ----------
            None

        Returns
        -------
            None
        """

        # load style settings from json file 
        with open("game/style_settings.json") as file:
            self.style_settings = json.load(file)

        # static variables
        self.resizable = self.style_settings["window"]["resizable"]
        self.colors = self.style_settings["colors"]
        self.piece_style = self.style_settings["pieces"]["piece_style"]
        self.piece_images = { # load piece images based on the selected style
            "P": pygame.image.load(f"game/img/{self.piece_style}/wP.svg"),
            "N": pygame.image.load(f"game/img/{self.piece_style}/wN.svg"),
            "B": pygame.image.load(f"game/img/{self.piece_style}/wB.svg"),
            "R": pygame.image.load(f"game/img/{self.piece_style}/wR.svg"),
            "Q": pygame.image.load(f"game/img/{self.piece_style}/wQ.svg"),
            "K": pygame.image.load(f"game/img/{self.piece_style}/wK.svg"),
            "p": pygame.image.load(f"game/img/{self.piece_style}/bP.svg"),
            "n": pygame.image.load(f"game/img/{self.piece_style}/bN.svg"),
            "b": pygame.image.load(f"game/img/{self.piece_style}/bB.svg"),
            "r": pygame.image.load(f"game/img/{self.piece_style}/bR.svg"),
            "q": pygame.image.load(f"game/img/{self.piece_style}/bQ.svg"),
            "k": pygame.image.load(f"game/img/{self.piece_style}/bK.svg"),
        }
        self.icon = pygame.image.load("game/img/icon.svg")

        # dynamic variables (change when window is resized)
        self.width = self.style_settings["window"]["width"]
        self.height = self.style_settings["window"]["height"]
        self.absolute_tile_width = None
        self.start_x_board = None
        self.start_y_board = None
        self.absolute_board_border_width = None
        self.absolute_active_square_border_width = None
        self.absolute_legal_move_circle_radius = None
        self.absolute_piece_width = None
        self.scaled_piece_images = {}

        self.update(self.width, self.height)

    def update(self, width, height):
        # set new width and height
        self.width = width
        self.height = height

        # recalculate dimension variables
        self.absolute_tile_width = round(self.height \
            * self.style_settings["tile_width"])
        self.start_x_board = round((self.width \
            - self.absolute_tile_width * 8) / 2) # x coordinate of the 
                                                 # leftmost point of the board
        self.start_y_board = round((self.height \
            - self.absolute_tile_width * 8) / 2) # y coordinate of the 
                                                 # uppermost point of the board
        self.absolute_board_border_width = round(self.height \
            * self.style_settings["board_border_width"])
        self.absolute_active_square_border_width = \
            round(self.absolute_tile_width \
            * self.style_settings["active_square_border_width"])
        self.absolute_legal_move_circle_radius = \
            round(self.absolute_tile_width \
            * self.style_settings["legal_move_circle_radius"])
        self.absolute_piece_width = round(self.absolute_tile_width \
            * self.style_settings["pieces"]["relative_piece_width"])

        # scale piece images to correct size
        for key, piece in self.piece_images.items():
            self.scaled_piece_images[key] = pygame.transform.scale(piece, 
                (self.absolute_piece_width, self.absolute_piece_width))


ds = DisplaySettings() # initialize display settings class

# create pygame screen oject
if ds.resizable:
    screen = pygame.display.set_mode((0, 0), pygame.RESIZABLE)
else:
    screen = pygame.display.set_mode((ds.width, ds.height))

# set icon and caption
pygame.display.set_icon(ds.icon)
pygame.display.set_caption("Thomas the Chess Engine")
