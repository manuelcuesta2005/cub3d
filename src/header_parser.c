/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:00:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/08/30 10:00:00 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	p_text(char **dst, char *line)
{
	char	*path;

	if (*dst)
		return (0);
	path = ft_strtrim(line + 3, " \n\r");
	if (!path)
		return (0);
	if (!file_exists(path))
		return (free(path), 0);
	*dst = path;
	return (1);
}

int	validate_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

int	parse_rgb_split(t_rgb *color, char **split)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (!validate_rgb_values(r, g, b))
		return (0);
	color->r = r;
	color->g = g;
	color->b = b;
	color->used = true;
	return (1);
}

int	p_rgb(t_rgb *color, char *line)
{
	char	**split;

	if (color->used == true)
		return (0);
	split = ft_split(line + 2, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		ft_matrix_free(&split);
		return (0);
	}
	if (!parse_rgb_split(color, split))
	{
		ft_matrix_free(&split);
		return (0);
	}
	ft_matrix_free(&split);
	return (1);
}
