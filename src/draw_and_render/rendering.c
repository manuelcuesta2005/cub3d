/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:06:00 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/30 05:05:33 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_background(t_game *game)
{
	int	ceiling_color;
	int	*buffer_color;
	int	floor_color;
	int	color;
	int	x;
	int	y;

	ceiling_color = set_rgb(&game->ceiling);
	floor_color = set_rgb(&game->floor);
	buffer_color = (int *)game->img->addr;
	y = 0;
	while (y < SCREEN_H)
	{
		if (y < SCREEN_H / 2)
			color = ceiling_color;
		else
			color = floor_color;
		x = 0;
		while (x < SCREEN_W)
		{
			buffer_color[y * (game->img->line_length / 4) + x] = color;
			x++;
		}
		y++;
	}
}

int	render_loop(t_game *game)
{
	draw_background(game);
	screen_columns(game->player, game, game->cast);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
}
