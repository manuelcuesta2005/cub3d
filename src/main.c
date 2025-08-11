/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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
		mlx_destroy_image(game->mlx, game->img_floor);
		mlx_destroy_image(game->mlx, game->img_player);
		mlx_destroy_image(game->mlx, game->img_wall);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		free(game);
	}
	exit(0);
}

static void	find_player(char **map, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E' || map[i][j] == 'S')
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
		free (game);
		exit(1);
	}
	//if (map_header(game->map, game) == 0)
	//{
	//	ft_printf("Error\n");
	//	free (game);
	//	exit(1);
	//}
	if (!map_validate(game))
	{
		ft_matrix_free(game->map);
		free(game);
		exit(1);
	}
	find_player(game->map, game);
}

static void	mlx_main(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return ;
	game->win = mlx_new_window(game->mlx,
			game->width * 64, game->height * 64, "so_long");
	if (!game->win)
		return ;
	load_images(game);
	game_render(game);
	mlx_key_hook(game->win, handle_key, game);
	mlx_hook(game->win, 17, 0, handle_exit, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (1);
	game = malloc(sizeof(t_game));
	map_main(argv[1], game);
	mlx_main(game);
	return (0);
}
