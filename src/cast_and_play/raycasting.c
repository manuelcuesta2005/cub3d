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
        cast->sideDistX = (cast->mapX - 1 - player->axisX) * cast->deltaDistX;
    }
    if (cast->rayDirY < 0)
    {
        cast->stepY = -1;
        cast->sideDistY = (player->axisY - cast->mapY) * cast->deltaDistY;
    }
    else
    {
        cast->stepY = 1;
        cast->sideDistY = (cast->mapY - 1 - player->axisY) * cast->deltaDistY;
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
            cast->side = 1;
        }
        else
        {
            cast->sideDistY += cast->deltaDistY;
            cast->mapY += cast->stepY;
            cast->side = 0;
        }
        if (game->map[cast->mapX][cast->mapY] == '1')
            cast->hit = 1;
    }
}

void screen_columns(t_player *player, t_game *game, t_cast *cast)
{
    int x;

    x = 0;
    while (x < SCREEN_W)
    {
        cast->cameraX = 2 * x / (double)game->width - 1;
        cast->rayDirX = player->visionX + player->planeX * cast->cameraX;
        cast->rayDirY = player->visionY + player->planeY * cast->cameraX;
        cast->mapX = (int)player->axisX;
        cast->mapY = (int)player->axisY;
        cast->deltaDistX = fabs(1 / cast->rayDirX);
        cast->deltaDistY = fabs(1 / cast->rayDirY);
        get_steps(player, cast);
        DDA_algorhitm(game, cast);
        if (cast->side == 0)
            cast->perpWallDist = (cast->mapX - player->axisX + (1 - cast->stepX) / 2) / cast->rayDirX;
        else
            cast->perpWallDist = (cast->mapY - player->axisY + (1 - cast->stepY) / 2) / cast->rayDirY;
        // Calcular altura en pantalla
        int lineHeight = (int)(SCREEN_H / cast->perpWallDist);

        int drawStart = -lineHeight / 2 + SCREEN_H / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_H / 2;
        if (drawEnd >= SCREEN_H)
            drawEnd = SCREEN_H - 1;

        // Color básico para probar (diferenciar lados)
        int color = (cast->side == 1) ? 0x00FF00 : 0xFF0000;

        // Dibujar línea vertical
        int y = drawStart;
        while (y < drawEnd)
        {
            mlx_pixel_put(game->mlx, game->win, x, y, color);
            y++;
        }
        x++;
    }
}
