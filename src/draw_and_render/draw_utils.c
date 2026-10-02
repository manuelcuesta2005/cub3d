/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:00:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/08/30 10:00:00 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	calc_limits(t_cast *cast, int *start, int *end)
{
	*start = -cast->line_height / 2 + SCREEN_H / 2;
	if (*start < 0)
		*start = 0;
	*end = cast->line_height / 2 + SCREEN_H / 2;
	if (*end >= SCREEN_H)
		*end = SCREEN_H - 1;
}

static int	calculate_tex_y(double tex_pos, int tex_height)
{
	int	tex_y;

	tex_y = (int)tex_pos % tex_height;
	if (tex_height < 0)
		tex_y += tex_height;
	return (tex_y);
}

static int	get_pixel_color(t_img *tex, int tex_x, int tex_y, int side)
{
	int	color;

	color = get_texture(tex, tex_x, tex_y);
	if (side == 1)
		color = (color >> 1) & 0x7F7F7F;
	return (color);
}

static void	draw_tex_column(t_game *game, t_cast *cast, int x, t_img *tex)
{
	double	step;
	double	tex_pos;
	int		y;
	int		start;
	int		end;

	calc_limits(cast, &start, &end);
	step = 1.0 * tex->height / cast->line_height;
	tex_pos = (start - SCREEN_H / 2 + cast->line_height / 2) * step;
	y = start;
	while (y < end)
	{
		paint_pixels(game->img, x, y,
			get_pixel_color(tex, cast->texture_x,
				calculate_tex_y(tex_pos, tex->height), cast->side));
		tex_pos += step;
		y++;
	}
}

void	draw_columns(t_game *game, t_cast *cast, int x)
{
	t_img	*tex;

	cast->line_height = (int)(SCREEN_H / cast->perp_wall_dist);
	tex = assign_texture(game, cast);
	cast->wall_x = get_wall_x(cast, game->player);
	cast->texture_x = (int)(cast->wall_x * (double)tex->width);
	if ((cast->side == 0 && cast->ray_dir_x > 0)
		|| (cast->side == 1 && cast->ray_dir_y < 0))
		cast->texture_x = tex->width - cast->texture_x - 1;
	draw_tex_column(game, cast, x, tex);
}
