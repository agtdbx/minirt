/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:22:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/27 17:23:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <memory.h>
# include <math.h>

# include "MLX42/MLX42.h"
# include "libft.h"

# define WIDTH 1920
# define HEIGHT 1080

////////////////////////////////////////////////////////////////////////////////
// STRUCTS

// Main struct
typedef struct s_all
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_all;

// Pixel (point in the screen) struct
typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

// Vector struct
typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

// Ray for raytracing struct
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

// Sphere struct
typedef struct s_sphere
{
	t_vector	origin;
	float		radius;
	float		radius2;
	int			color;
}	t_sphere;

// Plane struct
typedef struct s_plane
{
	t_vector	origin;
	t_vector	normal;
	t_vector	rev_normal;
	int			color;
}	t_plane;

// Cylinder struct
typedef struct s_cylinder
{
	t_vector	origin;
	t_vector	bot_origin;
	t_vector	top_origin;
	t_vector	axis;
	t_plane		bot;
	t_plane		top;
	float		radius;
	float		radius2;
	float		height;
	int			color;
}	t_cylinder;

// Intersect result struct
typedef struct s_dst_and_nrm
{
	t_vector	nrm;
	float		dst;
}	t_dst_and_nrm;

////////////////////////////////////////////////////////////////////////////////
// FILES

// main.c
void		render(t_all *all);
void		hook(void *param);
int			main(void);

// objets/sphere.c
t_sphere	create_sphere(t_vector origin, float radius, int color);
void		intersect_sphere(t_sphere *sphere, t_ray *ray,
				t_dst_and_nrm *dst_nrm);

// objets/plane.c
t_plane		create_plane(t_vector origin, t_vector normal, int color);
void		intersect_plane(t_plane *plane, t_ray *ray,
				t_dst_and_nrm *dst_nrm);

// objets/cylinder.c
t_cylinder	create_cylinder(t_vector origin, t_vector axis, float *size,
				int color);
void		intersect_cylinder(t_cylinder *cylinder, t_ray *ray,
				t_dst_and_nrm *dst_nrm);

// utils/vector.c
t_vector	create_vector(float x, float y, float z, bool normalize);
t_vector	multiply_vect_number(t_vector *vector, float number);
t_vector	add_vect_vect(t_vector *v1, t_vector *v2);
t_vector	sub_vect_vect(t_vector *v1, t_vector *v2);
float		dot_product(t_vector *v1, t_vector *v2);

// utils/print.c
void		print_vect(t_vector *vector);
void		print_ray(t_ray *ray);
void		print_sphere(t_sphere *sphere);

// utils/math_utils.c
float		solve_quadratic(float a, float b, float c);
t_vector	get_point_on_ray(t_ray *ray, float dist);

#endif
