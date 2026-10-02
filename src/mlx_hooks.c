/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:00:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/08/30 10:00:00 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_game	*g_game;

int	handle_close(void)
{
	handle_exit(g_game);
	return (0);
}

int	render_loop_wrapper(void)
{
	return (render_loop(g_game));
}

void	set_game_ptr(t_game *game)
{
	g_game = game;
}
