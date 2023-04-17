/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:56:58 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:14:37 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_ray_tab(t_ray **ray_tab, int max_alloc)
{
	int	i;

	i = 0;
	while (i < max_alloc)
	{
		free(ray_tab[i]);
		i++;
	}
	free(ray_tab);
}

t_ray	**alloc_ray_tab(void)
{
	int		y;
	t_ray	**ray_tab;

	ray_tab = malloc(sizeof(t_ray *) * HEIGHT);
	if (ray_tab == NULL)
		return (NULL);
	y = 0;
	while (y < HEIGHT)
	{
		ray_tab[y] = malloc(sizeof(t_ray) * WIDTH);
		if (ray_tab[y] == NULL)
		{
			free_ray_tab(ray_tab, y);
			return (NULL);
		}
		y++;
	}
	return (ray_tab);
}
