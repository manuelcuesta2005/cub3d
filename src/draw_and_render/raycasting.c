/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:04:07 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/30 05:06:20 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	get_steps(t_player *player, t_cast *cast)
{
	if (cast->ray_dir_x < 0)
	{
		cast->step_x = -1;
		cast->side_dist_x = (player->axis_x - cast->map_x) * cast->delta_dist_x;
	}
	else
	{
		cast->step_x = 1;
		cast->side_dist_x = (cast->map_x + 1.0 - player->axis_x)
			* cast->delta_dist_x;
	}
	if (cast->ray_dir_y < 0)
	{
		cast->step_y = -1;
		cast->side_dist_y = (player->axis_y - cast->map_y) * cast->delta_dist_y;
	}
	else
	{
		cast->step_y = 1;
		cast->side_dist_y = (cast->map_y + 1.0 - player->axis_y)
			* cast->delta_dist_y;
	}
}

void	dda_algorithm(t_game *game, t_cast *cast)
{
	cast->hit = 0;
	while (!cast->hit)
	{
		if (cast->side_dist_x < cast->side_dist_y)
		{
			cast->side_dist_x += cast->delta_dist_x;
			cast->map_x += cast->step_x;
			cast->side = 0;
		}
		else
		{
			cast->side_dist_y += cast->delta_dist_y;
			cast->map_y += cast->step_y;
			cast->side = 1;
		}
		if (game->map[cast->map_y][cast->map_x] == '1')
			cast->hit = 1;
	}
}

void	set_distance(t_cast *cast, t_player *player)
{
	if (cast->side == 0)
		cast->perp_wall_dist = (cast->map_x - player->axis_x
				+ (1 - cast->step_x) / 2) / cast->ray_dir_x;
	else
		cast->perp_wall_dist = (cast->map_y - player->axis_y
				+ (1 - cast->step_y) / 2) / cast->ray_dir_y;
}

void	screen_columns(t_player *player, t_game *game, t_cast *cast)
{
	int	x;

	x = 0;
	while (x < SCREEN_W)
	{
		cast->camera_x = 2 * x / (double)SCREEN_W - 1;
		cast->ray_dir_x = player->vision_x + player->plane_x * cast->camera_x;
		cast->ray_dir_y = player->vision_y + player->plane_y * cast->camera_x;
		cast->map_x = (int)player->axis_x;
		cast->map_y = (int)player->axis_y;
		if (cast->ray_dir_x == 0)
			cast->delta_dist_x = 1e30;
		else
			cast->delta_dist_x = fabs(1 / cast->ray_dir_x);
		if (cast->ray_dir_y == 0)
			cast->delta_dist_y = 1e30;
		else
			cast->delta_dist_y = fabs(1 / cast->ray_dir_y);
		get_steps(player, cast);
		dda_algorithm(game, cast);
		set_distance(cast, player);
		draw_columns(game, cast, x);
		x++;
	}
}
