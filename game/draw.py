import pygame
from static import *

# pygame screen object
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Thomas the Chess Engine")


def draw(draw_board, active_square, legal_moves, perspective):
    """Draws everything to the screen"""

    screen.fill(colors["white"])

    # draw chessboard and pieces
    for x in range(8):
        for y in range(8):
            # draw squares
            if (x + y) % 2 == 0: # light square
                pygame.draw.rect(screen, colors["light_squares"], 
                    (start_x_board + x * absolute_tile_width, 
                    start_y_board + y * absolute_tile_width,
                    absolute_tile_width, absolute_tile_width))
            else: # dark square
                pygame.draw.rect(screen, colors["dark_squares"], 
                    (start_x_board + x * absolute_tile_width, 
                    start_y_board + y * absolute_tile_width,
                    absolute_tile_width, absolute_tile_width))

            # draw pieces
            if perspective == "w":
                piece = draw_board[x][7 - y]
            else:
                piece = draw_board[7 - x][y]
            if piece != " ":
                screen.blit(piece_images[piece], (start_x_board + x \
                    * absolute_tile_width + round((absolute_tile_width \
                    - absolute_piece_width) / 2), start_y_board + y \
                    * absolute_tile_width + round((absolute_tile_width \
                    - absolute_piece_width) / 2)))

    # draw border around board
    pygame.draw.rect(screen, colors["board_border"], (start_x_board 
        - absolute_board_border_width, start_y_board 
        - absolute_board_border_width, 8 * absolute_tile_width 
        + 2 * absolute_board_border_width, absolute_board_border_width))
    pygame.draw.rect(screen, colors["board_border"], (start_x_board 
        - absolute_board_border_width, start_y_board 
        + 8 * absolute_tile_width, 8 * absolute_tile_width 
        + 2 * absolute_board_border_width, absolute_board_border_width))
    pygame.draw.rect(screen, colors["board_border"], (start_x_board 
        - absolute_board_border_width, start_y_board 
        - absolute_board_border_width, absolute_board_border_width, 
        8 * absolute_tile_width + 2 * absolute_board_border_width))
    pygame.draw.rect(screen, colors["board_border"], (start_x_board +
        8 * absolute_tile_width, start_y_board 
        - absolute_board_border_width, absolute_board_border_width, 
        8 * absolute_tile_width + 2 * absolute_board_border_width))

    if active_square:
        # adjust for perspective
        if perspective == "w":
            active_square = (active_square[0], 7 - active_square[1])
            legal_moves = [(move[0], 7 - move[1]) for move in legal_moves]
        else:
            active_square = (7 - active_square[0], active_square[1])
            legal_moves = [(7 - move[0], move[1]) for move in legal_moves]

        # draw active square
        pygame.draw.rect(screen, colors["white"], (start_x_board \
            + active_square[0] * absolute_tile_width, start_y_board \
            + active_square[1] * absolute_tile_width, absolute_tile_width, 
            absolute_active_square_border_width))
        pygame.draw.rect(screen, colors["white"], (start_x_board \
            + active_square[0] * absolute_tile_width, start_y_board \
            + absolute_tile_width - absolute_active_square_border_width \
            + active_square[1] * absolute_tile_width, absolute_tile_width, 
            absolute_active_square_border_width))
        pygame.draw.rect(screen, colors["white"], (start_x_board \
            + active_square[0] * absolute_tile_width, start_y_board \
            + active_square[1] * absolute_tile_width,
            absolute_active_square_border_width, absolute_tile_width,))
        pygame.draw.rect(screen, colors["white"], (start_x_board \
            + absolute_tile_width - absolute_active_square_border_width \
            + active_square[0] * absolute_tile_width, 
            start_y_board + active_square[1] * absolute_tile_width,
            absolute_active_square_border_width, absolute_tile_width,))

        # draw legal moves
        for move in legal_moves:
            pygame.draw.circle(screen, colors["legal_moves_circle"], 
                (start_x_board + round(absolute_tile_width / 2) + move[0] \
                * absolute_tile_width, start_y_board \
                + round(absolute_tile_width / 2) + move[1] \
                * absolute_tile_width), absolute_legal_move_circle_radius)

    pygame.display.flip()