/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:03:14 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/30 06:02:41 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	can_move(t_game *game, double new_x, double new_y)
{
	double	margin;

	margin = 0.2;
	if (new_x < margin || new_x >= game->width - margin
		|| new_y < margin || new_y >= game->height - margin)
		return (0);
	if (game->map[(int)new_y][(int)new_x] == '1'
		|| game->map[(int)(new_y + margin)][(int)new_x] == '1'
		|| game->map[(int)(new_y - margin)][(int)new_x] == '1'
		|| game->map[(int)new_y][(int)(new_x + margin)] == '1'
		|| game->map[(int)new_y][(int)(new_x - margin)] == '1')
		return (0);
	return (1);
}

void	move_player(t_game *game, t_player *player, double axis_x,
			double axis_y)
{
	double	position_x;
	double	position_y;

	position_x = player->axis_x + axis_x * player->move_speed;
	position_y = player->axis_y + axis_y * player->move_speed;
	if (can_move(game, position_x, player->axis_y))
		player->axis_x = position_x;
	if (can_move(game, player->axis_x, position_y))
		player->axis_y = position_y;
}

void	rotate_camera(t_player *player, double rotate_speed)
{
	double	sin_a;
	double	cos_a;
	double	old_dir_x;
	double	old_plane_x;

	sin_a = sin(rotate_speed);
	cos_a = cos(rotate_speed);
	old_dir_x = player->vision_x;
	player->vision_x = player->vision_x * cos_a - player->vision_y * sin_a;
	player->vision_y = old_dir_x * sin_a + player->vision_y * cos_a;
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos_a - player->plane_y * sin_a;
	player->plane_y = old_plane_x * sin_a + player->plane_y * cos_a;
}

int	key_hook(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game->player)
		return (0);
	if (keycode == KEY_W)
		move_player(game, game->player, game->player->vision_x,
			game->player->vision_y);
	else if (keycode == KEY_A)
		move_player(game, game->player, -game->player->vision_x,
			-game->player->vision_y);
	else if (keycode == KEY_S)
		move_player(game, game->player, -game->player->plane_x,
			-game->player->plane_y);
	else if (keycode == KEY_D)
		move_player(game, game->player, game->player->plane_x,
			game->player->plane_y);
	else if (keycode == KEY_RIGHT)
		rotate_camera(game->player, game->player->rotate_speed);
	else if (keycode == KEY_LEFT)
		rotate_camera(game->player, -game->player->rotate_speed);
	else if (keycode == 65307)
		handle_exit(game);
	return (0);
}

void	init_player(t_player **player, int x, int y, const char direction)
{
	(*player) = malloc(sizeof(t_player));
	if (!(*player))
		return ;
	(*player)->axis_x = x + 0.5;
	(*player)->axis_y = y + 0.5;
	(*player)->move_speed = 0.05;
	(*player)->rotate_speed = 0.05;
	if (direction == 'N')
	{
		(*player)->vision_x = 0;
		(*player)->vision_y = -1;
		(*player)->plane_x = 0.66;
		(*player)->plane_y = 0;
	}
	else
		start_position(*player, direction);
}
