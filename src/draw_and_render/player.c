/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:03:14 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/23 12:03:16 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int can_move(t_game *game, double newX, double newY)
{
	double	margin;

	margin = 0.2;

	if (newX < margin || newX >= game->width - margin || newY < margin || newY >= game->height - margin)
		return (0);
	if (game->map[(int)newY][(int)newX] == '1')
		return (0);
	return (1);
}

void move_player(t_game *game, t_player *player, double axisX, double axisY)
{
	double positionX;
	double positionY;

	positionX = player->axisX + axisX * player->moveSpeed;
	positionY = player->axisY + axisY * player->moveSpeed;
	if (can_move(game, positionX, player->axisY))
		player->axisX = positionX;
	if (can_move(game, player->axisX, positionY))
		player->axisY = positionY;
}

void rotate_camera(t_player *player, double rotateSpeed)
{
	double sin_a;
	double cos_a;
	double old_dirX;
	double old_planeX;

	sin_a = sin(rotateSpeed);
	cos_a = cos(rotateSpeed);
	old_dirX = player->visionX;
	player->visionX = player->visionX * cos_a - player->visionY * sin_a;
	player->visionY = old_dirX * sin_a + player->visionY * cos_a;
	old_planeX = player->planeX;
	player->planeX = player->planeX * cos_a - player->planeY * sin_a;
	player->planeY = old_planeX * sin_a + player->planeY * cos_a;
}

int key_hook(int keycode, t_player *player, t_game *game)
{
	if (!player)
		return (0);
	if (keycode == 119)
		move_player(game, player, player->visionX, player->visionY);
	else if (keycode == 115)
		move_player(game, player, -player->visionX, -player->visionY);
	else if (keycode == 97)
		move_player(game, player, -player->planeX, -player->planeY);
	else if (keycode == 100)
		move_player(game, player, player->planeX, player->planeY);
	else if (keycode == 65363)
		rotate_camera(player, player->rotateSpeed);
	else if (keycode == 65361)
		rotate_camera(player, -player->rotateSpeed);
	// else if (keycode == 65307)
	// 	close_window(game, "Close the game...");
	return (0);
}

void init_player(t_player **player, int x, int y, const char direction)
{
	(*player) = malloc(sizeof(t_player));
	if (!(*player))
		return ;
	(*player)->axisX = x + 0.5;
	(*player)->axisY = y + 0.5;
	(*player)->moveSpeed = 0.05;
	(*player)->rotateSpeed = 0.05;
	(*player)->angle = 0.66;
	if (direction == 'N')
    {
        (*player)->visionX = 0;
        (*player)->visionY = -1;
        (*player)->planeX = 0.66;
        (*player)->planeY = 0;
    }
	else
		start_position(*player, direction);
}
