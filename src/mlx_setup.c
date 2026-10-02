/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:00:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/08/30 10:00:00 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		handle_close(void);
int		render_loop_wrapper(void);
void	set_game_ptr(t_game *game);

static void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_free_game(game);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		ft_free_game(game);
		exit(1);
	}
}

static void	setup_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, render_loop_wrapper, NULL);
	mlx_key_hook(game->win, key_hook, game);
	mlx_hook(game->win, 17, 0, handle_close, NULL);
}

static void	setup_render_data(t_game *game)
{
	game->cast = malloc(sizeof(t_cast));
	game->img = malloc(sizeof(t_img));
	if (!game->img)
	{
		handle_exit(game);
		return ;
	}
	game->img->height = 64;
	game->img->width = 64;
	game->img->img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bpp,
			&game->img->line_length, &game->img->endian);
}

void	mlx_main(t_game *game)
{
	set_game_ptr(game);
	init_window(game);
	load_images(game);
	init_player(&game->player, game->player_x, game->player_y,
		game->map[game->player_y][game->player_x]);
	setup_render_data(game);
	if (!game->img)
		return ;
	setup_hooks(game);
	mlx_loop(game->mlx);
}
