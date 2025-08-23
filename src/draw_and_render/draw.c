/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:02:29 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/23 12:02:30 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int set_rgb(t_rgb *background)
{
    int color;

    color = (background->r << 16) | (background->g << 8) | background->b;
    return (color);
}

void    load_images(t_game *game)
{
    int width;
    int height;
    int i;

    width = 64;
    height = 64;
    i = 0;
    game->textures[0].img = mlx_xpm_file_to_image(game->mlx, game->tex_no, &width, &height);
    game->textures[1].img = mlx_xpm_file_to_image(game->mlx, game->tex_so, &width, &height);
    game->textures[2].img = mlx_xpm_file_to_image(game->mlx, game->tex_ea, &width, &height);
    game->textures[3].img = mlx_xpm_file_to_image(game->mlx, game->tex_we, &width, &height);
    while (i < 4)
    {
        game->textures[i].addr = mlx_get_data_addr(game->textures[i].img, &game->textures[i].bpp, &game->textures[i].line_length, &game->textures[i].endian);
        i++;
    }
}

int     get_texture(t_img *img, int x, int y)
{
    char    *dest;

    dest = img->addr + (y * img->line_length + x * (img->bpp / 8));
    return (*(unsigned int *)dest);
}

void    paint_pixels(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}


