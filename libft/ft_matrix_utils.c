/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:43:49 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/09 18:59:26 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matrix_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	**ft_matrix_duplicate(char **matrix)
{
	int		i;
	char	**matrix2;

	i = 0;
	while (matrix[i])
		i++;
	matrix2 = malloc(sizeof(char *) * (i + 1));
	if (!matrix2)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		matrix2[i] = ft_strdup(matrix[i]);
		if (!matrix2[i])
		{
			while (--i >= 0)
				free(matrix2[i]);
			free(matrix2);
			return (NULL);
		}
		i++;
	}
	matrix2[i] = NULL;
	return (matrix2);
}

void	ft_matrix_print(char **matrix, int jump)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		write(1, matrix[i], ft_strlen(matrix[i]));
		if (jump)
			write(1, "\n", 1);
		i++;
	}
}
