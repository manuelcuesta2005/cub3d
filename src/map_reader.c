/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:42:25 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/09 18:23:33 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	map_lines(char *map_name)
{
	int		fd;
	int		count_lines;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	count_lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		count_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count_lines);
}

static char	*normalize_line(char *line)
{
	int		len;
	char	*new_line;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		return (line);
	new_line = malloc(len + 2);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	ft_strlcpy(new_line, line, len + 1);
	new_line[len] = '\n';
	new_line[len + 1] = '\0';
	free(line);
	return (new_line);
}

static void	fill_map(char *map_name, char **map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exit(1);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		line = normalize_line(line);
		if (!line)
			exit(1);
		map[i] = ft_strdup(line);
		free(line);
		if (!map[i])
			exit(1);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
}

void	complete_map(t_game *game, char **map)
{
	int		i;
	int		max_len;
	int		j;
	int		len;
	char	*new_line;

	max_len = 0;
	i = game->lines_header - 1;
	while (map[++i])
	{
		len = ft_strlen(map[i]);
		while (len > 0 && (map[i][len - 1] == '\n' || map[i][len - 1] == '\r'))
			len--;
		if (len > max_len)
			max_len = len;
	}
	i = game->lines_header;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		while (len > 0 && (map[i][len - 1] == '\n' || map[i][len - 1] == '\r'))
			len--;
		if (len < max_len)
		{
			new_line = malloc(max_len + 2);
			if (!new_line)
				return ;
			for (j = 0; j < len; j++)
				new_line[j] = map[i][j];
			while (j < max_len)
				new_line[j++] = ' ';
			new_line[j++] = '\n';
			new_line[j] = '\0';
			free(map[i]);
			map[i] = new_line;
		}
		i++;
	}
}


void count_header(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if (!ft_strncmp(game->map[i], " ", 1) || !ft_strncmp(game->map[i], "0", 1) || !ft_strncmp(game->map[i], "1", 1))
			break ;
		i++;
	}
	game->lines_header = i - 1;
	ft_printf("Lines: %i\n", game->lines_header);
}

bool	map_reader(char *map_name, t_game *game)
{
	int		count_lines;
	size_t	len;

	if (!(ft_strnstr(".cub", &map_name[ft_strlen(map_name) - 4], 4)))
		return (ft_printf("Error\nExtension must be .cub\n"), 0);
	len = ft_strlen("maps/") + ft_strlen(map_name) + 1;
	game->route_map = malloc(len * sizeof(char));
	if (!game->route_map)
		return (ft_printf("(Error\nError malloc\n"), 0);
	game->route_map[0] = '\0';
	ft_strlcat(game->route_map, "maps/", len);
	ft_strlcat(game->route_map, map_name, len);
	count_lines = map_lines(game->route_map);
	if (count_lines == -1)
		return (ft_printf("Error\nMap not found\n"), 0);
	game->map = malloc((count_lines + 1) * sizeof(char *));
	if (!game->map)
		return (ft_printf("(Error\nError malloc\n"), 0);
	fill_map(game->route_map, game->map);
	count_header(game);
	complete_map(game, game->map);
	return (1);
}
