/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:45:18 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/08/30 08:58:31 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	find_player(char **map, t_game *game)
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

bool	count_header(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if (!ft_strncmp(game->map[i], " ", 1)
			|| !ft_strncmp(game->map[i], "0", 1)
			|| !ft_strncmp(game->map[i], "1", 1))
			break ;
		i++;
	}
	game->lines_header = i - 1;
	if (game->lines_header <= 0)
		return (0);
	return (1);
}

void	calculate_sizes(char **map, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (i == 0)
			game->width = j - 1;
		i++;
	}
	game->height = i;
}
