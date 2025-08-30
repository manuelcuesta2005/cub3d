/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:58:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/09 16:07:21 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	validate_limits(t_game *game)
{
	int	i;
	int	j;
	int	lim_i;
	int	lim_j;

	i = 0;
	lim_i = game->height - 1;
	lim_j = game->width;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (j < lim_j)
		{
			if (i == 0 || i == lim_i || j == 0 || j == lim_j - 1)
				if (game->map && game->map[i][j] != ' '
					&& game->map[i][j] != '1')
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static bool	validate_space(t_game *game, char **mp, int x, int y)
{
	int	height;
	int	width;

	width = game->width;
	height = game->height;
	if (y > 0 && mp[y - 1][x] && mp[y - 1][x] != ' ' && mp[y - 1][x] != '1')
		return (0);
	if (y + 1 < height
		&& mp[y + 1][x] && mp[y + 1][x] != ' ' && mp[y + 1][x] != '1')
		return (0);
	if (x > 0 && mp[y][x - 1] && mp[y][x - 1] != ' ' && mp[y][x - 1] != '1')
		return (0);
	if (x + 1 < width
		&& mp[y][x + 1] && mp[y][x + 1] != ' ' && mp[y][x + 1] != '1')
		return (0);
	return (1);
}

static bool	validate_spaces(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] && j < game->width)
		{
			if (game->map[i][j] == ' ')
				if (!validate_space(game, game->map, j, i))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	validate_chars(t_game *game, char **map, bool ini)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j + 1] && j < game->width - 1)
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
					|| map[i][j] == 'E') && !ini)
				ini = true;
			else if (!(map[i][j] == '\n' || map[i][j] == ' '
					|| map[i][j] == '1' || map[i][j] == '0'))
				return (0);
			j++;
		}
		i++;
	}
	if (ini)
		return (1);
	return (0);
}

bool	map_validate(t_game *game)
{
	calculate_sizes(game->map, game);
	if (!validate_limits(game))
	{
		ft_printf("Error\nLimits must be walls or spaces\n");
		return (0);
	}
	if (!validate_spaces(game))
	{
		ft_printf("Error\nSpaces must be surrounded by walls or spaces\n");
		return (0);
	}
	if (!validate_chars(game, game->map, false))
		return (ft_printf("Error\nCharacters map are invalid\n"), 0);
	return (1);
}
