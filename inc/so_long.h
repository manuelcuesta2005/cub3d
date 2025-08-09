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

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>

typedef struct s_game
{
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
} t_game;

typedef struct s_player
{
	double	axisX;
	double	axisY;
	double	visionX;
	double	visionY;
	double	planeX;
	double	planeY;
}	t_player;

	bool
	map_reader(char *map_name, t_game *game);
bool	map_validate(t_game *game);
bool	map_checker(t_game *game);

void	load_images(t_game *game);

void	game_render(t_game *game);
void	tile_render(t_game *game, int i, int j);
int	handle_key(int keycode, t_game *game);

int	handle_exit(t_game *game);

#endif