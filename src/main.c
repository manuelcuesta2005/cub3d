/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/04/07 22:42:25 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/09 19:03:25 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int	handle_exit(t_game *game)
{
	if (game)
	{
		if (game->map)
			ft_matrix_free(game->map);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_image(game->mlx, game->textures[0].img);
		mlx_destroy_image(game->mlx, game->textures[1].img);
		mlx_destroy_image(game->mlx, game->textures[2].img);
		mlx_destroy_image(game->mlx, game->textures[3].img);
		mlx_destroy_image(game->mlx, game->img->img);
		mlx_destroy_display(game->mlx);
		free(game->player);
		free(game->cast);
		free(game->mlx);
		free(game);
	}
	exit(0);
}

static void	find_player(char **map, t_game *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S')
			{
				game->player_y = i;
				game->player_x = j;
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}

void	map_main(char *map_name, t_game *game)
{
	if (map_reader(map_name, game) == 0)
	{
		ft_printf("Error\n");
		free(game);
		exit(1);
	}
	if (!map_validate(game))
	{
		ft_matrix_free(game->map);
		free(game);
		exit(1);
	}
	find_player(game->map, game);
}

static int	render_loop(t_game *game)
{
	draw_background(game);
	screen_columns(game->player, game, game->cast);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
}

static void	mlx_main(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return ;
	game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!game->win)
		return ;
	load_images(game);
	init_player(&game->player, game->player_x, game->player_y,
		game->map[game->player_y][game->player_x]);
	game->cast = malloc(sizeof(t_cast));
	game->img = malloc(sizeof(t_img));
	if (!game->img)
		return ;
	game->img->img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bpp,
			&game->img->line_length, &game->img->endian);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_hook(game->win, 17, 0, handle_exit, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game *game;

	if (argc != 2)
		return (1);
	game = malloc(sizeof(t_game));
	map_main(argv[1], game);
	mlx_main(game);
	return (0);
}
