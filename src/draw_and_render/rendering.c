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

static void	draw_ceiling(t_game *game, int color, int *buffer)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_H / 2)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			buffer[y * (game->img->line_length / 4) + x] = color;
			x++;
		}
		y++;
	}
}

static void	draw_floor(t_game *game, int color, int *buffer)
{
	int	x;
	int	y;

	y = SCREEN_H / 2;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			buffer[y * (game->img->line_length / 4) + x] = color;
			x++;
		}
		y++;
	}
}

void	draw_background(t_game *game)
{
	int	*buffer;

	buffer = (int *)game->img->addr;
	draw_ceiling(game, set_rgb(&game->ceiling), buffer);
	draw_floor(game, set_rgb(&game->floor), buffer);
}

int	render_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_background(game);
	screen_columns(game->player, game, game->cast);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
}
