/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:06:45 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/08/30 09:08:26 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_free_game(t_game *game)
{
	if (game->route_map)
		free(game->route_map);
	if (game->tex_ea)
		free(game->tex_ea);
	if (game->tex_no)
		free(game->tex_no);
	if (game->tex_so)
		free(game->tex_so);
	if (game->tex_we)
		free(game->tex_we);
	if (game->map)
		ft_matrix_free(game->map);
	free(game);
}

int	handle_exit(t_game *game)
{
	if (game)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_image(game->mlx, game->textures[0].img);
		mlx_destroy_image(game->mlx, game->textures[1].img);
		mlx_destroy_image(game->mlx, game->textures[2].img);
		mlx_destroy_image(game->mlx, game->textures[3].img);
		mlx_destroy_image(game->mlx, game->img->img);
		mlx_destroy_display(game->mlx);
		free(game->player);
		free(game->cast);
		free(game->img);
		free(game->mlx);
		ft_free_game(game);
	}
	exit(0);
}
