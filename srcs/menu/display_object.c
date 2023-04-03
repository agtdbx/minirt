/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/03 16:39:40 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_sphere(t_all *all, t_sphere *sphere)
{
	(void)sphere;
	mlx_put_string(all->mlx, "SPHERE", WIDTH - 240, 100);
}

void	display_plane(t_all *all, t_plane *plane)
{
	(void)plane;
	mlx_put_string(all->mlx, "PLANE", WIDTH - 230, 100);
}

void	display_cylinder(t_all *all, t_cylinder *cylinder)
{
	(void)cylinder;
	mlx_put_string(all->mlx, "CYLINDER", WIDTH - 250, 100);
}
