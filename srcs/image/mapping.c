/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:10:13 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/15 17:07:28 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_color	do_checkboard(float w, float h, float u, float v)
{
	t_color	res;

	res.r = 0;
	res.g = 0;
	res.b = 0;
	if (((int)(u * w) + (int)(v * h)) % 2)
	{
		res.r = 255;
		res.g = 255;
		res.b = 255;
	}
	return (res);
}

static t_color	do_texture(mlx_texture_t *texture, float u, float v)
{
	t_color	res;
	int		x;
	int		y;
	int		pixel_index;
	int		space_between_color;

	if (!texture)
	{
		res.r = 0;
		res.g = 0;
		res.b = 0;
		return res;
	}
	x = texture->width * u;
	y = texture->height * v;
	pixel_index = texture->width * y + x;
	space_between_color = texture->bytes_per_pixel / 3;
	res.r = texture->pixels[pixel_index * texture->bytes_per_pixel];
	res.g = texture->pixels[pixel_index * texture->bytes_per_pixel + space_between_color];
	res.b = texture->pixels[pixel_index * texture->bytes_per_pixel + (space_between_color * 2)];
	return (res);
}

t_color	sphere_map(t_ray const *ray, float dst, t_sphere const *sphere)
{
	float	theta;
	float	phi;
	float	raw_u;
	float	u;
	float	v;
	t_vec3	p;

	if (sphere->mapping_type == MAP_COLOR)
		return (sphere->color);
	p = get_point_on_ray(ray, dst);
	vec3_sub_vec3(&p, &sphere->origin);
	theta = atan2f(p.x, p.z);
	phi = acosf(p.y / vec3_get_length(&p));
	raw_u = theta / (2.0f * PI);
	u = 1.0f - (raw_u + 0.5f);
	v = 1.0f - (phi / PI);
	if (sphere->mapping_type == MAP_CHECKERBOARD)
		return (do_checkboard(8.0f, 8.0f, u, v));
	return (do_texture(sphere->texture_map, u, v));
}

t_color	plane_map(t_ray const *ray, float dst, t_plane const *plane)
{
	float	u;
	float	v;
	t_vec3	o_x;
	t_vec3	o_y;
	t_vec3	p;

	if (plane->mapping_type == MAP_COLOR)
		return (plane->color);
	p = get_point_on_ray(ray, dst);
	vec3_sub_vec3(&p, &plane->origin);
	if (plane->normal.x != 0.0f || plane->normal.y != 0.0f)
		vec3_fill(&o_y, -plane->normal.y, plane->normal.x, 0.0f);
	else
		vec3_fill(&o_y, 0.0f, 0.0f, 1.0f);
	vec3_cross_product(&plane->normal, &o_y, &o_x);
	vec3_normalize(&o_x);
	vec3_normalize(&o_y);
	u = vec3_dot_product(&o_x, &p);
	v = vec3_dot_product(&o_y, &p);
	u -= (int)u;
	v -= (int)v;
	u = (u + 1.0f) / 2.0f;
	v = (v + 1.0f) / 2.0f;
	if (plane->mapping_type == MAP_CHECKERBOARD)
		return (do_checkboard(8.0f, 8.0f, u, v));
	return (do_texture(plane->texture_map, u, v));
}

t_color	cylinder_map(t_ray const *ray, float dst, t_cylinder const *cylinder,
					float cy)
{
	t_vec3	ref; // vecteur de référence parallèle à Oxz (le sol)
	t_vec3	tmp;
	t_vec3	proj; // projeté de p sur le plan normal à axis
	float	cx;
	t_vec3	p;

	if (cylinder->mapping_type == MAP_COLOR)
		return (cylinder->color);
	p = get_point_on_ray(ray, dst);
	vec3_sub_vec3(&p, &cylinder->origin);
	if (cylinder->axis.x != 0.0f || cylinder->axis.y != 0.0f)
		vec3_fill(&ref, -cylinder->axis.y, cylinder->axis.x, 0.0f);
	else
		vec3_fill(&ref, 0.0f, 0.0f, 1.0f);
	vec3_cross_product(&cylinder->axis, &p, &tmp);
	vec3_cross_product(&cylinder->axis, &tmp, &proj);
	vec3_normalize(&ref);
	vec3_normalize(&proj);
	cx = acosf(vec3_dot_product(&proj, &ref));
	cx = cx / (2.0f * PI);
	vec3_cross_product(&cylinder->axis, &ref, &tmp);
	vec3_normalize(&tmp);
	if (vec3_dot_product(&proj, &tmp) < 0.0f)
		cx = 1.0f - cx;
	cy /= cylinder->height;
	if (cylinder->mapping_type == MAP_CHECKERBOARD)
		return (do_checkboard(16.0f, 8.0f, cx, cy));
	return (do_texture(cylinder->texture_map, cx, cy));
}
