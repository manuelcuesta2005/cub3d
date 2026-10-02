/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:49:01 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/09 16:36:13 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>

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
	bool	used;
	int		r;
	int		g;
	int		b;
}		t_rgb;

typedef struct s_cast
{
	int		hit;
	int		map_x;
	int		map_y;
	int		side;
	int		texture_x;
	int		line_height;
	double	pov;
	double	wall_x;
	double	step_x;
	double	step_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_y;
	double	delta_dist_x;
	double	perp_wall_dist;
}		t_cast;

typedef struct s_player
{
	double	axis_x;
	double	axis_y;
	double	vision_x;
	double	vision_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rotate_speed;
}		t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}		t_img;

typedef struct s_game
{
	char		*route_map;
	char		*tex_no;
	char		*tex_so;
	char		*tex_we;
	char		*tex_ea;
	t_rgb		floor;
	t_rgb		ceiling;
	t_img		textures[4];
	char		**map;
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	int			lines_header;
	t_player	*player;
	t_cast		*cast;
	t_img		*img;
}		t_game;

bool	map_reader(char *map_name, t_game *game);
bool	map_validate(t_game *game);
bool	map_checker(t_game *game);
int		map_header(t_game *game, char **map);
int		map_height(char **map);
void	find_player(char **map, t_game *game);
void	calculate_sizes(char **map, t_game *game);
bool	count_header(t_game *game);
void	complete_map(t_game *game, char **map);
void	load_images(t_game *game);
void	ft_free_game(t_game *game);
int		handle_exit(void *param);
void	init_game(t_game *game);
void	map_main(char *map_name, t_game *game);
void	mlx_main(t_game *game);
int		file_exists(char *path);
int		p_text(char **dst, char *line);
int		p_rgb(t_rgb *color, char *line);

// player and raycasting
int		set_rgb(t_rgb *background);
int		render_loop(void *param);
int		get_texture(t_img *img, int x, int y);
int		can_move(t_game *game, double new_x, double new_y);
int		key_hook(int keycode, void *param);
void	load_images(t_game *game);
void	paint_pixels(t_img *img, int x, int y, int color);
void	rotate_camera(t_player *player, double rotate_speed);
void	init_player(t_player **player, int x, int y, const char direction);
void	get_steps(t_player *player, t_cast *cast);
void	dda_algorithm(t_game *game, t_cast *cast);
void	set_distance(t_cast *cast, t_player *player);
void	draw_columns(t_game *game, t_cast *cast, int x);
void	screen_columns(t_player *player, t_game *game, t_cast *cast);
void	draw_background(t_game *game);
void	start_position(t_player *player, const char dir);
void	move_player(t_game *game, t_player *player, double axis_x,
			double axis_y);
t_img	*assign_texture(t_game *game, t_cast *cast);
double	get_wall_x(t_cast *cast, t_player *player);
void	cleanup_mlx(t_game *game);
void	init_mlx_data(t_game *game);

#endif