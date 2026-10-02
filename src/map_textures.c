/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:15:55 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/30 09:23:15 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	**create_new_map(t_game *game)
{
	int		total;
	int		i;
	int		j;
	char	**new_map;

	total = map_height(game->map);
	new_map = malloc((total - game->lines_header) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = game->lines_header + 1;
	j = 0;
	while (game->map[i])
	{
		new_map[j] = ft_strdup(game->map[i]);
		if (!new_map[j])
			return (NULL);
		j++;
		i++;
	}
	new_map[j] = NULL;
	return (new_map);
}

void	update_map_remove_header(t_game *game)
{
	char	**new_map;

	new_map = create_new_map(game);
	if (!new_map)
		return ;
	ft_matrix_free(&game->map);
	game->map = new_map;
}

static int	parse_header_line(t_game *game, char **map, int i, int *found)
{
	if (!ft_strncmp(map[i], "NO ", 3) && p_text(&game->tex_no, map[i]))
		(*found)++;
	else if (!ft_strncmp(map[i], "SO ", 3) && p_text(&game->tex_so, map[i]))
		(*found)++;
	else if (!ft_strncmp(map[i], "WE ", 3) && p_text(&game->tex_we, map[i]))
		(*found)++;
	else if (!ft_strncmp(map[i], "EA ", 3) && p_text(&game->tex_ea, map[i]))
		(*found)++;
	else if (!ft_strncmp(map[i], "F ", 2) && p_rgb(&game->floor, map[i]))
		(*found)++;
	else if (!ft_strncmp(map[i], "C ", 2) && p_rgb(&game->ceiling, map[i]))
		(*found)++;
	return (1);
}

int	map_header(t_game *game, char **map)
{
	int	i;
	int	found;

	found = 0;
	i = 0;
	game->ceiling.used = false;
	game->floor.used = false;
	while (i < game->lines_header && game->map[i])
	{
		parse_header_line(game, map, i, &found);
		i++;
	}
	update_map_remove_header(game);
	return (found == 6);
}
