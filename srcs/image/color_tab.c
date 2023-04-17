/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:23:51 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:15:09 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_color_tab(int **color_tab, int max_alloc)
{
	int	i;

	i = 0;
	while (i < max_alloc)
	{
		free(color_tab[i]);
		i++;
	}
	free(color_tab);
}

int	**alloc_color_tab(void)
{
	int	y;
	int	**color_tab;

	color_tab = malloc(sizeof(int *) * HEIGHT);
	if (color_tab == NULL)
		return (NULL);
	y = 0;
	while (y < HEIGHT)
	{
		color_tab[y] = malloc(sizeof(int) * WIDTH);
		if (color_tab[y] == NULL)
		{
			free_color_tab(color_tab, y);
			return (NULL);
		}
		y++;
	}
	return (color_tab);
}
