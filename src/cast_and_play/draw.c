#include "cub3d.h"

void load_images(t_game *game)
{
    int x;
    int y;

    game->img_floor = mlx_xpm_file_to_image(game->mlx,
                                            "textures/floor.xpm", &x, &y);
    game->img_wall = mlx_xpm_file_to_image(game->mlx,
                                           "textures/wall.xpm", &x, &y);
    game->img_player = mlx_xpm_file_to_image(game->mlx,
                                             "textures/player.xpm", &x, &y);
}

void    render_map(t_game *game)