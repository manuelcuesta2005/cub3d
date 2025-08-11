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
# include <stdbool.h>

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_game
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	t_rgb	floor;
	t_rgb	ceiling;
	char	**map;

	void	*img_player;
	void	*img_floor;
	void	*img_wall;

	void	*mlx;
	void	*win;

	int		width;
	int		height;
	int		player_x;
	int		player_y;
}		t_game;

typedef struct s_player
{
	double	axis_x;
	double	axis_y;
	double	vision_x;
	double	vision_y;
	double	plane_x;
	double	plane_y;
}	t_player;

bool	map_reader(char *map_name, t_game *game);
int		map_header(char **map, t_game *game);
bool	map_validate(t_game *game);
bool	map_checker(t_game *game);

void	load_images(t_game *game);

void	game_render(t_game *game);
void	tile_render(t_game *game, int i, int j);
int		handle_key(int keycode, t_game *game);

int		handle_exit(t_game *game);

#endif