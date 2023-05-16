/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   mapping.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aderouba <aderouba@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/15 11:10:13 by aderouba		  #+#	#+#			 */
/*   Updated: 2023/05/16 17:51:46 by aderouba		 ###   ########.fr	   */
/*																			*/
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

static t_vec3	mat_product(
			t_vec3 const *mat_1,
			t_vec3 const *mat_2,
			t_vec3 const *mat_3,
			t_vec3 const *lambda)
{
	t_vec3	result;

	result.x = 0.0f
		+ mat_1->x * lambda->x
		+ mat_2->x * lambda->y
		+ mat_3->x * lambda->z;
	result.y = 0.0f
		+ mat_1->y * lambda->x
		+ mat_2->y * lambda->y
		+ mat_3->y * lambda->z;
	result.z = 0.0f
		+ mat_1->z * lambda->x
		+ mat_2->z * lambda->y
		+ mat_3->z * lambda->z;
	return (result);
}

static void	do_normal_map(mlx_texture_t *texture, float u, float v, t_intersect_ret *ret, t_vec3 const *o_x, t_vec3 const *o_y, t_vec3 const *o_z)
{
	t_vec3	vec;
	int		x;
	int		y;
	int		pixel_index;
	int		space_between_color;

	if (!texture)
		return ;
	x = texture->width * u;
	y = texture->height * v;
	pixel_index = texture->width * y + x;
	space_between_color = texture->bytes_per_pixel / 3;
	vec.x = texture->pixels[pixel_index * texture->bytes_per_pixel] / 255.0f;
	vec.y = texture->pixels[pixel_index * texture->bytes_per_pixel + space_between_color] / 255.0f;
	vec.z = texture->pixels[pixel_index * texture->bytes_per_pixel + (space_between_color * 2)] / 255.0f;
	vec.x = (vec.x * 2.0f) - 1.0f;
	vec.y = (vec.y * 2.0f) - 1.0f;
	vec.z = (vec.z * 2.0f) - 1.0f;
	// print_vect(&vec);
	// vec3_normalize(&vec);
	// ret->nrm.x *= -vec.x;
	// ret->nrm.y *= -vec.y;
	// ret->nrm.z *= -vec.z;

	vec = mat_product(o_x, o_y, o_z, &vec);
	vec3_add_vec3(&ret->nrm, &vec);
	vec3_normalize(&ret->nrm);
}

t_color	sphere_map(t_ray const *ray, float dst, t_sphere const *sphere, t_intersect_ret *res)
{
	float	theta;
	float	phi;
	float	raw_u;
	float	u;
	float	v;
	t_vec3	p;

	(void)res;
	p = get_point_on_ray(ray, dst);
	vec3_sub_vec3(&p, &sphere->origin);
	theta = atan2f(p.x, p.z);
	phi = acosf(p.y / vec3_get_length(&p));
	raw_u = theta / (2.0f * PI);
	u = 1.0f - (raw_u + 0.5f);
	v = 1.0f - (phi / PI);
	// if (sphere->normal_map)
	// 	do_normal_map(sphere->normal_map, u, v, res);
	if (sphere->mapping_type == MAP_COLOR)
		return (sphere->color);
	else if (sphere->mapping_type == MAP_CHECKERBOARD)
		return (do_checkboard(8.0f, 8.0f, u, v));
	return (do_texture(sphere->texture_map, u, v));
}

t_color	plane_map(t_ray const *ray, float dst, t_plane const *plane, t_intersect_ret *res)
{
	float	u;
	float	v;
	t_vec3	o_x;
	t_vec3	o_y;
	t_vec3	p;

	p = get_point_on_ray(ray, dst);
	vec3_sub_vec3(&p, &plane->origin);
	if (plane->normal.x != 0.0f || plane->normal.y != 0.0f)
		vec3_fill(&o_y, -plane->normal.y, plane->normal.x, 0.0f);
	else
		vec3_fill(&o_y, 0.0f, 1.0f, 0.0f);
	vec3_cross_product(&plane->normal, &o_y, &o_x);
	vec3_normalize(&o_x);
	vec3_normalize(&o_y);
	u = vec3_dot_product(&o_x, &p) / 3.0f;
	v = vec3_dot_product(&o_y, &p) / 3.0f;
	u -= (int)u;
	v -= (int)v;
	if (u > 0.0f)
		u = 1.0f - u;
	else
		u = fabs(u);
	if (v > 0.0f)
		v = 1.0f - v;
	else
		v = fabs(v);
	if (plane->normal_map)
		do_normal_map(plane->normal_map, u, v, res, &o_x, &o_y, &plane->normal);
	if (plane->mapping_type == MAP_COLOR)
		return (plane->color);
	else if (plane->mapping_type == MAP_CHECKERBOARD)
		return (do_checkboard(8.0f, 8.0f, u, v));
	return (do_texture(plane->texture_map, u, v));
}

t_color	cylinder_map(t_ray const *ray, float dst, t_cylinder const *cylinder,
					float cy, t_intersect_ret *res)
{
	t_vec3	ref; // vecteur de référence parallèle à Oxz (le sol)
	t_vec3	tmp;
	t_vec3	proj; // projeté de p sur le plan normal à axis
	float	cx;
	t_vec3	p;

	(void)res;
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
	// if (cylinder->normal_map)
	// 	do_normal_map(cylinder->normal_map, cx, cy, res);
	if (cylinder->mapping_type == MAP_COLOR)
		return (cylinder->color);
	else if (cylinder->mapping_type == MAP_CHECKERBOARD)
		return (do_checkboard(16.0f, 8.0f, cx, cy));
	return (do_texture(cylinder->texture_map, cx, cy));
}
