/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:04:07 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/23 12:04:12 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void get_steps(t_player *player, t_cast *cast)
{
    if (cast->rayDirX < 0)
    {
        cast->stepX = -1;
        cast->sideDistX = (player->axisX - cast->mapX) * cast->deltaDistX;
    }
    else
    {
        cast->stepX = 1;
        cast->sideDistX = (cast->mapX + 1.0 - player->axisX) * cast->deltaDistX;
    }
    if (cast->rayDirY < 0)
    {
        cast->stepY = -1;
        cast->sideDistY = (player->axisY - cast->mapY) * cast->deltaDistY;
    }
    else
    {
        cast->stepY = 1;
        cast->sideDistY = (cast->mapY + 1.0 - player->axisY) * cast->deltaDistY;
    }
}

void DDA_algorhitm(t_game *game, t_cast *cast)
{
    cast->hit = 0;
    while (!cast->hit)
    {
        if (cast->sideDistX < cast->sideDistY)
        {
            cast->sideDistX += cast->deltaDistX;
            cast->mapX += cast->stepX;
            cast->side = 0;
        }
        else
        {
            cast->sideDistY += cast->deltaDistY;
            cast->mapY += cast->stepY;
            cast->side = 1;
        }
        if (game->map[cast->mapY][cast->mapX] == '1')
            cast->hit = 1;
    }
}

void set_distance(t_cast *cast, t_player *player)
{
    if (cast->side == 0)
        cast->perpWallDist = (cast->mapX - player->axisX + (1 - cast->stepX) / 2) / cast->rayDirX;
    else
        cast->perpWallDist = (cast->mapY - player->axisY + (1 - cast->stepY) / 2) / cast->rayDirY;
}

static void calc_limits(t_cast *cast, int *start, int *end, int h)
{
    *start = cast->line_height / 2 + h / 2;
    if (*start < 0)
        *start = 0;
    *end = cast->line_height / 2 + h / 2;
    if (*end >= h)
        *end = h - 1;
}

static void	draw_tex_column(t_game *game, t_cast *cast, int x, t_img *tex)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;
	int		start;
	int		end;

	calc_limits(cast, &start, &end, game->height);
	step = 1.0 * tex->height / cast->line_height;
	tex_pos = (start - game->height / 2 + cast->line_height / 2) * step;
	y = start;
	while (y < end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = get_texture(tex, cast->textureX, tex_y);
		if (cast->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		paint_pixels(game->img, x, y, color);
		y++;
	}
}

void	draw_columns(t_game *game, t_cast *cast, int x)
{
	double	wallX;
	t_img	*tex;

	cast->line_height = (int)(game->height / cast->perpWallDist);
	tex = assign_texture(game);
	wallX = get_wall_X(cast, game->player);
	cast->textureX = (int)(wallX * (double)tex->width);
	if ((cast->side == 0 && cast->rayDirX > 0) ||
		(cast->side == 1 && cast->rayDirY < 0))
		cast->textureX = tex->width - cast->textureX - 1;
	draw_tex_column(game, cast, x, tex);
}

void screen_columns(t_player *player, t_game *game, t_cast *cast)
{
    int x;

    x = 0;
    while (x < SCREEN_W)
    {
        cast->cameraX = 2 * x / (double)SCREEN_W - 1;
        cast->rayDirX = player->visionX + player->planeX * cast->cameraX;
        cast->rayDirY = player->visionY + player->planeY * cast->cameraX;
        cast->mapX = (int)player->axisX;
        cast->mapY = (int)player->axisY;
        cast->deltaDistX = fabs(1 / cast->rayDirX);
        cast->deltaDistY = fabs(1 / cast->rayDirY);
        get_steps(player, cast);
        DDA_algorhitm(game, cast);
        set_distance(cast, player);
        draw_columns(game, cast, x);
        x++;
    }
}

