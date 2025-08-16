/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+	+:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:++#+        */
/*                                                +#+#+#+#+#+	+#+           */
/*   Created: 2024/12/07 22:49:01 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/09 16:36:13 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265358979323846
typedef struct s_rgb
{
	int r;
	int g;
	int b;
} t_rgb;

typedef struct s_cast
{
	int		 hit;
    int      mapX;
    int      mapY;
    int      side;
	double	 pov;
	double	 stepX;
	double	 stepY;
    double   cameraX;
    double   rayDirX;
    double   rayDirY;
	double	 sideDistX;
	double	 sideDistY;
    double   deltaDistY;
    double   deltaDistX;
    double   perpWallDist;
}	t_cast; 

typedef struct s_player
{
	double axisX;
	double axisY;
	double visionX;
	double visionY;
	double planeX;
	double planeY;
	double moveSpeed;
	double rotateSpeed;
	double angle;
} t_player;

typedef struct s_game
{
	char *tex_no;
	char *tex_so;
	char *tex_we;
	char *tex_ea;
	t_rgb floor;
	t_rgb ceiling;
	char **map;
	void *img_player;
	void *img_floor;
	void *img_wall;
	void *mlx;
	void *win;
	int width;
	int height;
	int player_x;
	int player_y;
	t_player *player;
} t_game;


bool map_reader(char *map_name, t_game *game);
int map_header(char **map, t_game *game);
bool map_validate(t_game *game);
bool map_checker(t_game *game);
void load_images(t_game *game);
void game_render(t_game *game);
void tile_render(t_game *game, int i, int j);
int handle_key(int keycode, t_game *game);
int handle_exit(t_game *game);

// player and raycast
void start_position(t_player *player, char *dir);
#endif