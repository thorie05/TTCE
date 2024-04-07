import pygame
import json


class DisplaySettings():
    """
    A class containing static and dynamic variables for displaying the game.

    Attributes
    ----------
        resizable : bool, static
            resizable or fixed size screen
        colors : List[List[int, int , int]]
            list containing different colors in rgb format
        piece_style : str, static
            which piece style should be used for the piece sprites
        piece_sprites : Dict[str, pygame.surface.Surface], static
            list containing the sprite for each piece
        icon : pygame.surface.Surface, static
            pygame icon
        width : int
            width of the game window
        height : int
            height of the game window
        tile_width : int
            width of a tile on the chessboard in pixels
        start_x_board : int
            x-coordinate of the leftmost point of the chessboard
        start_y_board : int
            y-coordinate of the uppermost point of the chessboard
        board_border_width : int
            thickness of the board border in pixels
        active_square_border_width : int
            thickness of the border around the active square in pixels
        legeal_moves_circle_radius : int
            radius of the circle for highlighting legal moves
        piece_width : int
            width of the piece sprites
        scaled_piece_sprites : Dict[str, pygame.surface.Surface]
            list containing the sprite for each piece scaled to fit the screen

    Methods
    -------
        update(width, height):
            Updates the dynamic variables using the new window width and height.
    """

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
        self.piece_sprites = { # load piece sprites based on the selected style
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
        self.tile_width = None
        self.start_x_board = None
        self.start_y_board = None
        self.board_border_width = None
        self.active_square_border_width = None
        self.legal_move_circle_radius = None
        self.piece_width = None
        self.scaled_piece_sprites = {}

        self.update(self.width, self.height)

    def update(self, width, height):
        """
        Updates the dynamic variables using the new window width and height.

        Parameters
        ----------
            width : int
                new width of the screen
            height : int
                new height of the screen

        Returns
        -------
            None
        """

        # set new width and height
        self.width = width
        self.height = height

        # recalculate dimension variables
        self.tile_width = round(self.height * self.style_settings["tile_width"])
        self.start_x_board = round((self.width - self.tile_width * 8) / 2)
        self.start_y_board = round((self.height - self.tile_width * 8) / 2)
        self.board_border_width = round(self.height \
            * self.style_settings["board_border_width"])
        self.active_square_border_width = round(self.tile_width \
            * self.style_settings["active_square_border_width"])
        self.legal_move_circle_radius = round(self.tile_width \
            * self.style_settings["legal_move_circle_radius"])
        self.piece_width = round(self.tile_width \
            * self.style_settings["pieces"]["relative_piece_width"])

        # scale piece sprites to correct size
        for key, piece in self.piece_sprites.items():
            self.scaled_piece_sprites[key] = pygame.transform.scale(piece, 
                (self.piece_width, self.piece_width))


ds = DisplaySettings() # initialize display settings class

# create pygame screen oject
if ds.resizable:
    screen = pygame.display.set_mode((0, 0), pygame.RESIZABLE)
else:
    screen = pygame.display.set_mode((ds.width, ds.height))

# set icon and caption
pygame.display.set_icon(ds.icon)
pygame.display.set_caption("Thomas the Chess Engine")
