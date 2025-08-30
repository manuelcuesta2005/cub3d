/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_complete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:54:28 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/08/30 08:55:50 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	line_effective_len(char *s)
{
	int	len;

	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
		len--;
	return (len);
}

static int	get_max_len(char **map, int start)
{
	int	i;
	int	len;
	int	max;

	i = start;
	max = 0;
	while (map[i])
	{
		len = line_effective_len(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static int	pad_to_len(char **line_ptr, int target)
{
	char	*new_line;
	int		len;
	int		i;

	len = line_effective_len(*line_ptr);
	if (len >= target)
		return (1);
	new_line = malloc(target + 2);
	if (!new_line)
		return (0);
	i = 0;
	while (i < len)
	{
		new_line[i] = (*line_ptr)[i];
		i++;
	}
	while (i < target)
		new_line[i++] = ' ';
	new_line[i++] = '\n';
	new_line[i] = '\0';
	free(*line_ptr);
	*line_ptr = new_line;
	return (1);
}

// función principal ----------------------------------------------------

void	complete_map(t_game *game, char **map)
{
	int	i;
	int	max_len;

	max_len = get_max_len(map, game->lines_header);
	i = game->lines_header;
	while (map[i])
	{
		if (!pad_to_len(&map[i], max_len))
			return ;
		i++;
	}
}
