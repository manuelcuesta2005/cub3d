/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:31:01 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/09 16:07:21 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	player_moves(t_game *game, int new_y, int new_x)
{
	if (game->map[new_y][new_x] == '0')
	{
		game->map[game->player_y][game->player_x] = '0';
		game->map[new_y][new_x] = 'E';
		game->player_y = new_y;
		game->player_x = new_x;
	}
	else
		return (0);
	return (1);
}

static void	handle_key_result(int result, t_game *game, int keycode)
{
	static int	moves;

	if (!moves)
		moves = 0;
	if (result == 1)
	{
		ft_printf("%i\n", ++moves);
		tile_render(game, game->player_y, game->player_x);
		if (keycode == 119)
			tile_render(game, game->player_y + 1, game->player_x);
		if (keycode == 97)
			tile_render(game, game->player_y, game->player_x + 1);
		if (keycode == 115)
			tile_render(game, game->player_y - 1, game->player_x);
		if (keycode == 100)
			tile_render(game, game->player_y, game->player_x - 1);
	}
}

int	handle_key(int keycode, t_game *game)
{
	int			result;

	result = 0;
	if (keycode == 65307)
		handle_exit(game);
	else if (keycode == 119)
		result = player_moves(game, game->player_y - 1, game->player_x);
	else if (keycode == 97)
		result = player_moves(game, game->player_y, game->player_x - 1);
	else if (keycode == 115)
		result = player_moves(game, game->player_y + 1, game->player_x);
	else if (keycode == 100)
		result = player_moves(game, game->player_y, game->player_x + 1);
	handle_key_result(result, game, keycode);
	return (0);
}
