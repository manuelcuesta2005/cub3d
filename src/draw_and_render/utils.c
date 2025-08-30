/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:06:38 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/30 05:05:16 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	start_position(t_player *player, const char dir)
{
	if (dir == 'S')
	{
		player->visionX = 0;
		player->visionY = 1;
		player->planeX = -0.66;
		player->planeY = 0;
	}
	else if (dir == 'E')
	{
		player->visionX = 1;
		player->visionY = 0;
		player->planeX = 0;
		player->planeY = 0.66;
	}
	else if (dir == 'W')
	{
		player->visionX = -1;
		player->visionY = 0;
		player->planeX = 0;
		player->planeY = -0.66;
	}
}

t_img	*assign_texture(t_game *game, t_cast *cast)
{
	if (cast->side == 0 && cast->rayDirX > 0)
		return (&game->textures[0]);
	else if (cast->side == 0 && cast->rayDirX < 0)
		return (&game->textures[1]);
	else if (cast->side == 1 && cast->rayDirY > 0)
		return (&game->textures[2]);
	else
		return (&game->textures[3]);
}

double	get_wall_X(t_cast *cast, t_player *player)
{
	double	wallX;

	if (cast->side == 0)
		wallX = player->axisY + cast->perpWallDist * cast->rayDirY;
	else
		wallX = player->axisX + cast->perpWallDist * cast->rayDirX;
	return (wallX - floor(wallX));
}
