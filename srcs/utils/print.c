/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:34:31 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/01 18:50:58 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_vect(t_vector *vector)
{
	printf("vec (%03.3f, %03.3f, %03.3f)\n", vector->x, vector->y, vector->z);
}

void	print_ray(t_ray *ray)
{
	printf("ray (%03.3f, %03.3f, %03.3f) -> (%03.3f, %03.3f, %03.3f)\n",
		ray->origin.x, ray->origin.y, ray->origin.z,
		ray->direction.x, ray->direction.y, ray->direction.z);
}

void	print_sphere(t_sphere *sphere)
{
	int	color;
	int	r;
	int	g;
	int	b;

	color = sphere->color;
	g = color >> 16;
	r = (color >> 24) & 0XFF;
	g = (color >> 16) & 0XFF;
	b = (color >> 8) & 0XFF;
	printf("sphere (%03.3f, %03.3f, % 03.3f), r = %03.3f, color = (%i, %i, %i)\n",
		sphere->origin.x, sphere->origin.y, sphere->origin.z,
		sphere->radius,
		r, g, b);
}

void	print_plane(t_plane *plane)
{
	int	color;
	int	r;
	int	g;
	int	b;

	color = plane->color;
	g = color >> 16;
	r = (color >> 24) & 0XFF;
	g = (color >> 16) & 0XFF;
	b = (color >> 8) & 0XFF;
	printf("plane (%03.3f, %03.3f, %03.3f), nrm = (%03.3f, %03.3f, %03.3f), color = (%i, %i, %i)\n",
		plane->origin.x, plane->origin.y, plane->origin.z,
		plane->normal.x, plane->normal.y, plane->normal.z,
		r, g, b);
}

void	print_cylinder(t_cylinder *cylinder)
{
	int	color;
	int	r;
	int	g;
	int	b;

	color = cylinder->color;
	g = color >> 16;
	r = (color >> 24) & 0XFF;
	g = (color >> 16) & 0XFF;
	b = (color >> 8) & 0XFF;
	printf("cylinder (%03.3f, %03.3f, %03.3f), axis = (%03.3f, %03.3f, %03.3f), d = %03.3f, length = %03.3f, color = (%i, %i, %i)\n",
		cylinder->origin.x, cylinder->origin.y, cylinder->origin.z,
		cylinder->axis.x, cylinder->axis.y, cylinder->axis.z,
		cylinder->radius * 2, cylinder->height,
		r, g, b);
}

void	print_ambiant_light(t_scene *scene)
{
	int	color;
	int	r;
	int	g;
	int	b;

	color = scene->al_color;
	g = color >> 16;
	r = (color >> 24) & 0XFF;
	g = (color >> 16) & 0XFF;
	b = (color >> 8) & 0XFF;
	printf("Ambient light : intensity = %03.3f, color = (%i, %i, %i)\n",
		scene->al_intensity, r, g, b);
}

void	print_camera(t_scene *scene)
{
	printf("Camera : pos = (%03.3f, %03.3f, %03.3f), orientation = (%03.3f, %03.3f, % 03.3f), fov = %i\n",
		scene->camera.pos.x, scene->camera.pos.y, scene->camera.pos.z,
		scene->camera.orientation.x, scene->camera.orientation.y, scene->camera.orientation.z,
		scene->camera.fov);
}

void	print_light(t_scene *scene)
{
	int	color;
	int	r;
	int	g;
	int	b;

	color = scene->light.color;
	g = color >> 16;
	r = (color >> 24) & 0XFF;
	g = (color >> 16) & 0XFF;
	b = (color >> 8) & 0XFF;
	printf("Light : pos = (%03.3f, %03.3f, %03.3f), intensity = %03.3f, color = (%i, %i, %i)\n",
		scene->light.pos.x, scene->light.pos.y, scene->light.pos.z,
		scene->light.brightness, r, g, b);
}

void	print_rtlst(t_rtlst *rtlst)
{
	t_rtlst	*tmp;

	tmp = rtlst;
	printf("==============================rtlst==============================\n");
	while (tmp)
	{
		if (tmp->type == SPHERE)
			print_sphere(&tmp->value.as_sphere);
		else if (tmp->type == PLANE)
			print_plane(&tmp->value.as_plane);
		else if (tmp->type == CYLINDER)
			print_cylinder(&tmp->value.as_cylinder);
		tmp = tmp->next;
	}
	printf("=================================================================\n");
}
