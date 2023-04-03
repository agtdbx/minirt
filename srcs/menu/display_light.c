/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:35:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/03 16:39:27 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_ambiant_light(t_all *all, t_light *ambiant_light)
{
	(void)ambiant_light;
	mlx_put_string(all->mlx, "AMBIANT LIGHT", WIDTH - 270, 100);
}

void	display_light(t_all *all, t_light *light)
{
	(void)light;
	mlx_put_string(all->mlx, "LIGHT", WIDTH - 230, 100);
}
