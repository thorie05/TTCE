import pygame
from display_settings import ds, screen
from draw import draw
from events import events


class PromotionPopup():
    """
    A class managing the popup window that appears when a pawn is promoted.

    Attributes
    ----------
        color : str
            color of the promoting player (w or b)
        board : List[List[str]]
            current piece arrangement
        active_square : Tuple[int, int]
            square currently selected by the player, i.e. active square
        legal_moves : List[Tuple[Tuple[int, int]]]
            list of legal moves of the piece standing on the selected square
        perspective : str
            perspective of the player (w or b)

    Methods
    -------
        draw():
            Draws everything to the screen.
        run():
            Opens the promotin popup window and returns the selected piece.

    """

    def __init__(self, color, draw_board, active_square, legal_moves,
        perspective):
        """
        Initializes the PromotionPopup class.

        Parameters
        ----------
            color : str
                color of the promoting player (w or b)
            board : List[List[str]]
                current piece arrangement
            active_square : Tuple[int, int]
                square currently selected by the player, i.e. active square
            legal_moves : List[Tuple[Tuple[int, int]]]
                list of legal moves of the piece standing on the selected square
            perspective : str
                perspective of the player (w or b)

        Returns
        -------
            None
        """

        self.color = color
        self.draw_board = draw_board
        self.active_square = active_square
        self.legal_moves = legal_moves
        self.perspective = perspective

    def draw(self):
        """
        Draws everything to the screen.

        Parameters
        ----------
            None

        Returns
        -------
            None
        """

        # calculate starting coordinates of the popup window
        x_pos = round((ds.width - ds.promotion_popup_width) / 2)
        y_pos = round((ds.height - ds.promotion_popup_height) / 2)

        # draw popup box with border
        pygame.draw.rect(screen, ds.colors["board_border"],
            (x_pos, y_pos, ds.promotion_popup_width, ds.promotion_popup_height))
        pygame.draw.rect(screen, ds.colors["light_squares"],
            (x_pos + ds.board_border_width, y_pos + ds.board_border_width,
            ds.promotion_popup_width - 2* ds.board_border_width,
            ds.promotion_popup_height - 2 * ds.board_border_width))

        # draw text
        text = "Choose piece for promotion."
        font_size = round(ds.promotion_popup_font_size)
        promotion_text = ds.fonts[font_size].render(text, True,
            ds.colors["board_border"])
        font_pos_x = x_pos + round((ds.promotion_popup_width \
            - promotion_text.get_width()) / 2)
        font_pos_y = y_pos + 0.15 * ds.promotion_popup_height
        screen.blit(promotion_text, (font_pos_x, font_pos_y))

        # draw pieces
        pieces = ["N", "B", "R", "Q"]
        if self.color == "b":
            pieces = [piece.lower() for piece in pieces]
        for i, piece in enumerate(pieces):
            screen.blit(ds.scaled_piece_sprites[piece], self.piece_positions[i])

        pygame.display.flip()

    def run(self):
        """
        Opens the promotin popup window and returns the selected piece.

        Paramters
        ---------
            None

        Returns
        -------
            promotion_piece : str
                promotion piece selected by the player
        """

        promotion_piece = None

        # main loop runs until the player selects a piece
        while not promotion_piece:
            # calculate coordinates of the pieces to choose from
            self.piece_positions = [(round((ds.width \
                - ds.promotion_popup_width) / 2) + round(
                (ds.promotion_popup_width - 4 * ds.piece_width) / 2) + i \
                * ds.piece_width, round((ds.height - ds.piece_width) / 2 \
                + 0.07 * ds.promotion_popup_height)) for i in range(4)]

            event = events(self.perspective)

            # handle events
            if event.event_type == "click":
                pos1 = pygame.mouse.get_pos()
                # if player clicked inside a piece
                for p, pos2 in zip(["n", "b", "r", "q"], self.piece_positions):
                    x1, y1 = pos1
                    x2, y2 = pos2
                    if x1 >= x2 and x1 <= x2 + ds.piece_width \
                    and y1 >= y2 and y1 <= y2 + ds.piece_width:
                        return p
            elif event.event_type == "resized":
                new_width, new_height = pygame.display.get_surface().get_size()
                ds.update(new_width, new_height)

            draw(self.draw_board, self.active_square, self.legal_moves,
                self.perspective, self)

        return promotion_piece