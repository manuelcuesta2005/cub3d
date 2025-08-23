/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:06:00 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/23 12:06:01 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void    draw_background(t_game *game)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < SCREEN_H / 2)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            paint_pixels(game->img, x, y, set_rgb(&game->ceiling));
            x++;
        }
        y++;
    }
    y = 0;
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            paint_pixels(game->img, x, y, set_rgb(&game->floor));
            x++;
        }
        y++;
    }
}

