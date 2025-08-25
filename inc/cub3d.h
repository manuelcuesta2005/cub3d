/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/12/07 22:49:01 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/09 16:36:13 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>

# define PI 3.14159265358979323846
# define SCREEN_W 1080
# define SCREEN_H 600
# define KEY_W 119
# define KEY_A 115
# define KEY_S 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_rgb
{
	int r;
	int g;
	int b;
} t_rgb;

typedef struct s_cast
{
	int hit;
	int mapX;
	int mapY;
	int side;
	int textureX;
	int line_height;
	double pov;
	double wallX;
	double stepX;
	double stepY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	double sideDistX;
	double sideDistY;
	double deltaDistY;
	double deltaDistX;
	double perpWallDist;
} t_cast;

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

typedef struct s_img
{
	void *img;
	char *addr;
	int bpp;
	int line_length;
	int endian;
	int height;
	int width;
} t_img;

typedef struct s_game
{
	char *tex_no;
	char *tex_so;
	char *tex_we;
	char *tex_ea;
	t_rgb floor;
	t_rgb ceiling;
	t_img textures[4];
	char **map;
	void *mlx;
	void *win;
	int width;
	int height;
	int player_x;
	int player_y;
	t_player *player;
	t_cast *cast;
	t_img *img;
} t_game;

bool	map_reader(char *map_name, t_game *game);
bool	map_validate(t_game *game);
bool	map_checker(t_game *game);
int		map_header(t_game *game);
void	load_images(t_game *game);


int		handle_exit(t_game *game);

// player and raycasting
int		set_rgb(t_rgb *background);
int		get_texture(t_img *img, int x, int y);
int		can_move(t_game *game, double newX, double newY);
int		key_hook(int keycode, t_game *game);
void	load_images(t_game *game);
void	paint_pixels(t_img *img, int x, int y, int color);
void	rotate_camera(t_player *player, double rotateSpeed);
void	init_player(t_player **player, int x, int y, const char direction);
void	get_steps(t_player *player, t_cast *cast);
void	DDA_algorhitm(t_game *game, t_cast *cast);
void	set_distance(t_cast *cast, t_player *player);
void	draw_columns(t_game *game, t_cast *cast, int x);
void	screen_columns(t_player *player, t_game *game, t_cast *cast);
void	draw_background(t_game *game);
void	start_position(t_player *player, const char dir);
void	move_player(t_game *game, t_player *player, double axisX,
		double axisY);
t_img	*assign_texture(t_game *game);
double	get_wall_X(t_cast *cast, t_player *player);

#endif