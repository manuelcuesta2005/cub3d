/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:15:55 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/08/30 08:33:36 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	p_text(char **dst, char *line)
{
	char	*path;

	path = ft_strtrim(line + 3, " \n\r");
	if (!path)
		return (0);
	if (!file_exists(path))
		return (free(path), 0);
	*dst = path;
	return (1);
}

static int	p_rgb(t_rgb *color, char *line)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(line + 2, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (ft_matrix_free(split), 0);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_matrix_free(split), 0);
	color->r = r;
	color->g = g;
	color->b = b;
	ft_matrix_free(split);
	return (1);
}

static int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	update_map_remove_header(t_game *game)
{
	int		total;
	int		i;
	int		j;
	char	**new_map;

	total = map_height(game->map);
	new_map = malloc((total - game->lines_header) * sizeof(char *));
	if (!new_map)
		return ;
	i = game->lines_header + 1;
	j = 0;
	while (game->map[i])
	{
		new_map[j] = ft_strdup(game->map[i]);
		if (!new_map[j])
			return ;
		j++;
		i++;
	}
	new_map[j] = NULL;
	ft_matrix_free(game->map);
	game->map = new_map;
}


int	map_header(t_game *game)
{
	int		i;
	int		found;
	char	**map;

	map = game->map;
	found = 0;
	i = 0;
	while (i < game->lines_header && game->map[i])
	{
		if (!ft_strncmp(map[i], "NO ", 3) && p_text(&game->tex_no, map[i]))
			found++;
		else if (!ft_strncmp(map[i], "SO ", 3) && p_text(&game->tex_so, map[i]))
			found++;
		else if (!ft_strncmp(map[i], "WE ", 3) && p_text(&game->tex_we, map[i]))
			found++;
		else if (!ft_strncmp(map[i], "EA ", 3) && p_text(&game->tex_ea, map[i]))
			found++;
		else if (!ft_strncmp(map[i], "F ", 2) && p_rgb(&game->floor, map[i]))
			found++;
		else if (!ft_strncmp(map[i], "C ", 2) && p_rgb(&game->ceiling, map[i]))
			found++;
		i++;
	}
	if (found == 6)
		return (update_map_remove_header(game), 1);
	return (0);
}
