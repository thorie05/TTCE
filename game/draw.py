import pygame
from display_settings import ds, screen


def draw(draw_board, active_square, legal_moves, perspective,
    promotion_popup=None):
    """
    Draws everything to the screen.
    
    Parameters
    ----------
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

    screen.fill(ds.colors["white"]) # clear last screen with white color

    # draw chessboard and pieces
    for x in range(8):
        for y in range(8):
            # draw squares
            if (x + y) % 2 == 0: # light square
                pygame.draw.rect(screen, ds.colors["light_squares"], 
                    (ds.start_x_board + x * ds.tile_width, ds.start_y_board \
                    + y * ds.tile_width, ds.tile_width, ds.tile_width))
            else: # dark square
                pygame.draw.rect(screen, ds.colors["dark_squares"], 
                    (ds.start_x_board + x * ds.tile_width, ds.start_y_board \
                    + y * ds.tile_width, ds.tile_width, ds.tile_width))

            # account for players perspective
            if perspective == "w":
                piece = draw_board[x][7 - y] # account for perspe
            else:
                piece = draw_board[7 - x][y]

            # draw pieces
            if piece != " ":
                screen.blit(ds.scaled_piece_sprites[piece], (ds.start_x_board \
                    + x * ds.tile_width + round((ds.tile_width \
                    - ds.piece_width) / 2), ds.start_y_board \
                    + y * ds.tile_width + round((ds.tile_width \
                    - ds.piece_width) / 2)))

    # draw border around board
    pygame.draw.rect(screen, ds.colors["board_border"], (ds.start_x_board
        - ds.board_border_width, ds.start_y_board - ds.board_border_width,
        8 * ds.tile_width + 2 * ds.board_border_width, ds.board_border_width))
    pygame.draw.rect(screen, ds.colors["board_border"], (ds.start_x_board 
        - ds.board_border_width, ds.start_y_board + 8 * ds.tile_width,
        8 * ds.tile_width + 2 * ds.board_border_width, ds.board_border_width))
    pygame.draw.rect(screen, ds.colors["board_border"], (ds.start_x_board
        - ds.board_border_width, ds.start_y_board - ds.board_border_width,
        ds.board_border_width, 8 * ds.tile_width + 2 * ds.board_border_width))
    pygame.draw.rect(screen, ds.colors["board_border"], (ds.start_x_board +
        8 * ds.tile_width, ds.start_y_board - ds.board_border_width, 
        ds.board_border_width, 8 * ds.tile_width + 2 * ds.board_border_width))

    # draw active square and legal moves
    if active_square:
        # account for players perspective
        if perspective == "w":
            active_square = (active_square[0], 7 - active_square[1])
            legal_moves = [(move[0], 7 - move[1]) for move in legal_moves]
        else:
            active_square = (7 - active_square[0], active_square[1])
            legal_moves = [(7 - move[0], move[1]) for move in legal_moves]

        # draw active square
        pygame.draw.rect(screen, ds.colors["white"], (ds.start_x_board \
            + active_square[0] * ds.tile_width, ds.start_y_board \
            + active_square[1] * ds.tile_width, ds.tile_width, 
            ds.active_square_border_width))
        pygame.draw.rect(screen, ds.colors["white"], (ds.start_x_board \
            + active_square[0] * ds.tile_width, ds.start_y_board \
            + ds.tile_width - ds.active_square_border_width + active_square[1] \
            * ds.tile_width, ds.tile_width, ds.active_square_border_width))
        pygame.draw.rect(screen, ds.colors["white"], (ds.start_x_board \
            + active_square[0] * ds.tile_width, ds.start_y_board \
            + active_square[1] * ds.tile_width, ds.active_square_border_width, 
            ds.tile_width,))
        pygame.draw.rect(screen, ds.colors["white"], (ds.start_x_board \
            + ds.tile_width - ds.active_square_border_width + active_square[0] \
            * ds.tile_width, ds.start_y_board + active_square[1] \
            * ds.tile_width, ds.active_square_border_width, ds.tile_width,))

        # draw legal moves
        for move in legal_moves:
            pygame.draw.circle(screen, ds.colors["legal_moves_circle"], 
                (ds.start_x_board + round(ds.tile_width / 2) + move[0] \
                * ds.tile_width, ds.start_y_board + round(ds.tile_width / 2) \
                + move[1] * ds.tile_width), ds.legal_move_circle_radius)

    # draw promotion popup
    if promotion_popup:
        promotion_popup.draw()

    # flip screen to show changes
    pygame.display.flip()
