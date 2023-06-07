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
	t_color	color_ul;
	t_color	color_ur;
	t_color	color_dl;
	t_color	color_dr;
	t_color	color_u;
	t_color	color_d;
	int		x;
	int		y;
	int		nx;
	int		ny;
	float	dx;
	float	dy;
	float	inv_dx;
	float	inv_dy;
	int		pixel_index;
	int		space_between_color;

	if (!texture)
	{
		res.r = 0;
		res.g = 0;
		res.b = 0;
		return (res);
	}

	dx = (float)texture->width * u;
	dy = (float)texture->height * v;
	x = (float)texture->width * u;
	y = (float)texture->height * v;
	dx -= x;
	dy -= y;
	inv_dx = 1.0f - dx;
	inv_dy = 1.0f - dy;

	space_between_color = texture->bytes_per_pixel / 3;

	if (x == (int)texture->width - 1 || y == (int)texture->height - 1)
	{
		nx = 0;
		ny = 0;
	}
	else
	{
		nx = x + 1;
		ny = y + 1;
	}

	// UL
	pixel_index = texture->width * y + x;
	color_ul.r = texture->pixels[pixel_index * texture->bytes_per_pixel];
	color_ul.g = texture->pixels[pixel_index * texture->bytes_per_pixel + space_between_color];
	color_ul.b = texture->pixels[pixel_index * texture->bytes_per_pixel + (space_between_color * 2)];

	// UR
	pixel_index = texture->width * y + nx;
	color_ur.r = texture->pixels[pixel_index * texture->bytes_per_pixel];
	color_ur.g = texture->pixels[pixel_index * texture->bytes_per_pixel + space_between_color];
	color_ur.b = texture->pixels[pixel_index * texture->bytes_per_pixel + (space_between_color * 2)];

	// DL
	pixel_index = texture->width * ny + x;
	color_dl.r = texture->pixels[pixel_index * texture->bytes_per_pixel];
	color_dl.g = texture->pixels[pixel_index * texture->bytes_per_pixel + space_between_color];
	color_dl.b = texture->pixels[pixel_index * texture->bytes_per_pixel + (space_between_color * 2)];

	// DR
	pixel_index = texture->width * ny + nx;
	color_dr.r = texture->pixels[pixel_index * texture->bytes_per_pixel];
	color_dr.g = texture->pixels[pixel_index * texture->bytes_per_pixel + space_between_color];
	color_dr.b = texture->pixels[pixel_index * texture->bytes_per_pixel + (space_between_color * 2)];

	// Color up
	color_u.r = (float)color_ul.r * inv_dx + (float)color_ur.r * dx;
	color_u.g = (float)color_ul.g * inv_dx + (float)color_ur.g * dx;
	color_u.b = (float)color_ul.b * inv_dx + (float)color_ur.b * dx;

	// Color down
	color_d.r = (float)color_dl.r * inv_dx + (float)color_dr.r * dx;
	color_d.g = (float)color_dl.g * inv_dx + (float)color_dr.g * dx;
	color_d.b = (float)color_dl.b * inv_dx + (float)color_dr.b * dx;

	// Result color
	res.r = (float)color_u.r * inv_dy + (float)color_d.r * dy;
	res.g = (float)color_u.g * inv_dy + (float)color_d.g * dy;
	res.b = (float)color_u.b * inv_dy + (float)color_d.b * dy;

	return (res);
}

// static t_color	do_texture(mlx_texture_t *texture, float u, float v)
// {
// 	t_color	res;
// 	int		x;
// 	int		y;
// 	int		pixel_index;
// 	int		space_between_color;

// 	if (!texture)
// 	{
// 		res.r = 0;
// 		res.g = 0;
// 		res.b = 0;
// 		return res;
// 	}
// 	x = texture->width * u;
// 	y = texture->height * v;
// 	pixel_index = texture->width * y + x;
// 	space_between_color = texture->bytes_per_pixel / 3;
// 	res.r = texture->pixels[pixel_index * texture->bytes_per_pixel];
// 	res.g = texture->pixels[pixel_index * texture->bytes_per_pixel + space_between_color];
// 	res.b = texture->pixels[pixel_index * texture->bytes_per_pixel + (space_between_color * 2)];
// 	return (res);
// }

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



static void	do_normal_map(
				mlx_texture_t *texture,
				float u,
				float v,
				t_intersect_ret *ret,
				t_vec3 const *o_x,
				t_vec3 const *o_y,
				t_vec3 const *o_z)
{
	t_vec3	new_nrm;
	t_vec3	nrm_ul;
	t_vec3	nrm_ur;
	t_vec3	nrm_dl;
	t_vec3	nrm_dr;
	t_vec3	nrm_u;
	t_vec3	nrm_d;
	int		x;
	int		y;
	int		nx;
	int		ny;
	float	dx;
	float	dy;
	float	inv_dx;
	float	inv_dy;
	int		pixel_index;
	int		space_between_color;

	if (!texture)
		return ;
	dx = (float)texture->width * u;
	dy = (float)texture->height * v;
	x = (float)texture->width * u;
	y = (float)texture->height * v;
	dx -= x;
	dy -= y;
	inv_dx = 1.0f - dx;
	inv_dy = 1.0f - dy;
	space_between_color = texture->bytes_per_pixel / 3;

	if (x == (int)texture->width - 1 || y == (int)texture->height - 1)
	{
		nx = 0;
		ny = 0;
	}
	else
	{
		nx = x + 1;
		ny = y + 1;
	}

	// UL
	pixel_index = texture->width * y + x;
	nrm_ul.x = texture->pixels[pixel_index *
				texture->bytes_per_pixel] / 255.0f;
	nrm_ul.y = texture->pixels[pixel_index *
				texture->bytes_per_pixel + space_between_color] / 255.0f;
	nrm_ul.z = texture->pixels[pixel_index *
				texture->bytes_per_pixel + (space_between_color * 2)] / 255.0f;

	// UR
	pixel_index = texture->width * y + nx;
	nrm_ur.x = texture->pixels[pixel_index *
				texture->bytes_per_pixel] / 255.0f;
	nrm_ur.y = texture->pixels[pixel_index *
				texture->bytes_per_pixel + space_between_color] / 255.0f;
	nrm_ur.z = texture->pixels[pixel_index *
				texture->bytes_per_pixel + (space_between_color * 2)] / 255.0f;

	// DL
	pixel_index = texture->width * ny + x;
	nrm_dl.x = texture->pixels[pixel_index *
				texture->bytes_per_pixel] / 255.0f;
	nrm_dl.y = texture->pixels[pixel_index *
				texture->bytes_per_pixel + space_between_color] / 255.0f;
	nrm_dl.z = texture->pixels[pixel_index *
				texture->bytes_per_pixel + (space_between_color * 2)] / 255.0f;

	// DR
	pixel_index = texture->width * ny + nx;
	nrm_dr.x = texture->pixels[pixel_index *
				texture->bytes_per_pixel] / 255.0f;
	nrm_dr.y = texture->pixels[pixel_index *
				texture->bytes_per_pixel + space_between_color] / 255.0f;
	nrm_dr.z = texture->pixels[pixel_index *
				texture->bytes_per_pixel + (space_between_color * 2)] / 255.0f;

	// Color up
	nrm_u.x = nrm_ul.x * inv_dx + nrm_ur.x * dx;
	nrm_u.y = nrm_ul.y * inv_dx + nrm_ur.y * dx;
	nrm_u.z = nrm_ul.z * inv_dx + nrm_ur.z * dx;

	// Color down
	nrm_d.x = nrm_dl.x * inv_dx + nrm_dr.x * dx;
	nrm_d.y = nrm_dl.y * inv_dx + nrm_dr.y * dx;
	nrm_d.z = nrm_dl.z * inv_dx + nrm_dr.z * dx;

	// Result color
	new_nrm.x = nrm_u.x * inv_dy + nrm_d.x * dy;
	new_nrm.y = nrm_u.y * inv_dy + nrm_d.y * dy;
	new_nrm.z = nrm_u.z * inv_dy + nrm_d.z * dy;

	new_nrm.x = (new_nrm.x * 2.0f) - 1.0f;
	new_nrm.y = (new_nrm.y * 2.0f) - 1.0f;
	new_nrm.z = (new_nrm.z * 2.0f) - 1.0f;

	new_nrm.x *= -1;
	new_nrm.y *= -1;
	new_nrm = mat_product(o_x, o_y, o_z, &new_nrm);
	vec3_dup(&ret->nrm, &new_nrm);
	vec3_normalize(&ret->nrm);
}

// static void	do_normal_map(
// 				mlx_texture_t *texture,
// 				float u,
// 				float v,
// 				t_intersect_ret *ret,
// 				t_vec3 const *o_x,
// 				t_vec3 const *o_y,
// 				t_vec3 const *o_z)
// {
// 	t_vec3	new_nrm;
// 	int		x;
// 	int		y;
// 	int		pixel_index;
// 	int		space_between_color;

// 	if (!texture)
// 		return ;
// 	x = texture->width * u;
// 	y = texture->height * v;
// 	pixel_index = texture->width * y + x;
// 	space_between_color = texture->bytes_per_pixel / 3;
// 	new_nrm.x = texture->pixels[pixel_index *
// 				texture->bytes_per_pixel] / 255.0f;
// 	new_nrm.y = texture->pixels[pixel_index *
// 				texture->bytes_per_pixel + space_between_color] / 255.0f;
// 	new_nrm.z = texture->pixels[pixel_index *
// 				texture->bytes_per_pixel + (space_between_color * 2)] / 255.0f;
// 	new_nrm.x = (new_nrm.x * 2.0f) - 1.0f;
// 	new_nrm.y = (new_nrm.y * 2.0f) - 1.0f;
// 	new_nrm.z = (new_nrm.z * 2.0f) - 1.0f;

// 	new_nrm.x *= -1;
// 	new_nrm.y *= -1;
// 	new_nrm = mat_product(o_x, o_y, o_z, &new_nrm);
// 	vec3_dup(&ret->nrm, &new_nrm);
// 	vec3_normalize(&ret->nrm);
// }

t_color	sphere_map(t_ray const *ray, float dst, t_sphere const *sphere, t_intersect_ret *res)
{
	float	theta;
	float	phi;
	float	raw_u;
	float	u;
	float	v;
	t_vec3	p;
	t_vec3	o_x;
	t_vec3	o_y;

	p = get_point_on_ray(ray, dst);
	vec3_sub_vec3(&p, &sphere->origin);
	theta = atan2f(p.x, p.z);
	phi = acosf(p.y / vec3_get_length(&p));
	raw_u = theta / (2.0f * PI);
	u = 1.0f - (raw_u + 0.5f);
	v = 1.0f - (phi / PI);
	if (sphere->normal_map)
	{
		vec3_fill(&o_y, 0.0f, -1.0f, 0.0f);
		vec3_cross_product(&res->nrm, &o_y, &o_x);
		vec3_normalize(&o_x);
		do_normal_map(sphere->normal_map, u, v, res, &o_x, &o_y, &res->nrm);
	}
	if (sphere->mapping_type == MAP_COLOR)
		return (sphere->color);
	else if (sphere->mapping_type == MAP_CHECKERBOARD)
		return (do_checkboard(8.0f, 8.0f, u, v));
	return (do_texture(sphere->texture_map, u, v));
}

t_color	plane_map(
			t_ray const *ray,
			float dst,
			t_plane const *plane,
			t_intersect_ret *res)
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
		do_normal_map(plane->normal_map, u, v, res, &o_x, &o_y, &res->nrm);
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
	if (cylinder->normal_map)
	{
		vec3_cross_product(&cylinder->axis, &res->nrm, &tmp);
		vec3_normalize(&tmp);
		vec3_multiply_number(&tmp, -1.0f);
		vec3_dup(&ref, &cylinder->axis);
		vec3_multiply_number(&ref, -1.0f);
		do_normal_map(cylinder->normal_map, cx, cy, res, &tmp, &ref, &res->nrm);
	}
	if (cylinder->mapping_type == MAP_COLOR)
		return (cylinder->color);
	else if (cylinder->mapping_type == MAP_CHECKERBOARD)
		return (do_checkboard(16.0f, 8.0f, cx, cy));
	return (do_texture(cylinder->texture_map, cx, cy));
}


t_color	cone_map(t_ray const *ray, float dst, t_cone const *cone,
					float cy, t_intersect_ret *res)
{
	t_vec3	ref; // vecteur de référence parallèle à Oxz (le sol)
	t_vec3	tmp;
	t_vec3	proj; // projeté de p sur le plan normal à axis
	float	cx;
	t_vec3	p;

	p = get_point_on_ray(ray, dst);
	vec3_sub_vec3(&p, &cone->origin);
	if (cone->axis.x != 0.0f || cone->axis.y != 0.0f)
		vec3_fill(&ref, -cone->axis.y, cone->axis.x, 0.0f);
	else
		vec3_fill(&ref, 0.0f, 0.0f, 1.0f);
	vec3_cross_product(&cone->axis, &p, &tmp);
	vec3_cross_product(&cone->axis, &tmp, &proj);
	vec3_normalize(&ref);
	vec3_normalize(&proj);
	cx = acosf(vec3_dot_product(&proj, &ref));
	cx = cx / (2.0f * PI);
	vec3_cross_product(&cone->axis, &ref, &tmp);
	vec3_normalize(&tmp);
	if (vec3_dot_product(&proj, &tmp) < 0.0f)
		cx = 1.0f - cx;
	cy /= cone->height;
	if (cone->normal_map)
	{
		vec3_cross_product(&cone->axis, &res->nrm, &tmp);
		vec3_normalize(&tmp);
		vec3_multiply_number(&tmp, -1.0f);
		vec3_dup(&ref, &cone->axis);
		vec3_multiply_number(&ref, -1.0f);
		do_normal_map(cone->normal_map, cx, cy, res, &tmp, &ref, &res->nrm);
	}
	if (cone->mapping_type == MAP_COLOR)
		return (cone->color);
	else if (cone->mapping_type == MAP_CHECKERBOARD)
		return (do_checkboard(16.0f, 8.0f, cx, cy));
	return (do_texture(cone->texture_map, cx, cy));
}
