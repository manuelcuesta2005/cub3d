/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:06:45 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/08/30 09:08:26 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cleanup_mlx(t_game *game)
{
	if (game->textures[0].img)
		mlx_destroy_image(game->mlx, game->textures[0].img);
	if (game->textures[1].img)
		mlx_destroy_image(game->mlx, game->textures[1].img);
	if (game->textures[2].img)
		mlx_destroy_image(game->mlx, game->textures[2].img);
	if (game->textures[3].img)
		mlx_destroy_image(game->mlx, game->textures[3].img);
	if (game->img && game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
}

void	init_mlx_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->player = NULL;
	game->cast = NULL;
	game->img = NULL;
	game->textures[0].img = NULL;
	game->textures[1].img = NULL;
	game->textures[2].img = NULL;
	game->textures[3].img = NULL;
}
