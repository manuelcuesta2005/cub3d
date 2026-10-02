/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:00:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/08/30 10:00:00 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_game(t_game *game)
{
	game->route_map = NULL;
	game->tex_ea = NULL;
	game->tex_no = NULL;
	game->tex_so = NULL;
	game->tex_we = NULL;
	game->map = NULL;
	init_mlx_data(game);
}

void	map_main(char *map_name, t_game *game)
{
	init_game(game);
	if (map_reader(map_name, game) == 0)
	{
		ft_free_game(game);
		exit(1);
	}
	if (map_header(game, game->map) == 0)
	{
		ft_printf("Error\nHeader not valid\n");
		ft_free_game(game);
		exit(1);
	}
	if (!map_validate(game))
	{
		ft_free_game(game);
		exit(1);
	}
	find_player(game->map, game);
}
