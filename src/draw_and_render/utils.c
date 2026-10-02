/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:06:38 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/30 09:08:54 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	start_position(t_player *player, const char dir)
{
	if (dir == 'S')
	{
		player->vision_x = 0;
		player->vision_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'E')
	{
		player->vision_x = 1;
		player->vision_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->vision_x = -1;
		player->vision_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

t_img	*assign_texture(t_game *game, t_cast *cast)
{
	if (cast->side == 0 && cast->ray_dir_x > 0)
		return (&game->textures[0]);
	else if (cast->side == 0 && cast->ray_dir_x < 0)
		return (&game->textures[1]);
	else if (cast->side == 1 && cast->ray_dir_y > 0)
		return (&game->textures[2]);
	else
		return (&game->textures[3]);
}

double	get_wall_x(t_cast *cast, t_player *player)
{
	double	wall_x;

	if (cast->side == 0)
		wall_x = player->axis_y + cast->perp_wall_dist * cast->ray_dir_y;
	else
		wall_x = player->axis_x + cast->perp_wall_dist * cast->ray_dir_x;
	return (wall_x - floor(wall_x));
}
