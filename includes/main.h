/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:22:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/25 11:44:59 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
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
	int			color;
}	t_plane;

// Cylinder struct
typedef struct s_cylinder
{
	t_vector	origin;
	t_vector	direction;
	float		diameter;
	float		height;
	int			color;
}	t_cylinder;

////////////////////////////////////////////////////////////////////////////////
// FILES

// main.c
void	render(t_all *all);
void	hook(void *param);
int		main(void);

// objets/sphere.c
t_sphere	create_sphere(t_vector origin, int radius, int color);
float		intersect_sphere(t_sphere *sphere, t_ray *ray);

// objets/plane.c
t_plane		create_plane(t_vector origin, t_vector direction, int color);
float		intersect_plane(t_plane *plane , t_ray *ray);

// utils/vector.c
t_vector	create_vector(float x, float y, float z, int normalize);
t_vector	multiply_vect_number(t_vector *vector, float number);
t_vector	add_vect_vect(t_vector *v1, t_vector *v2);
t_vector	sub_vect_vect(t_vector *v1, t_vector *v2);
float		dot_product(t_vector *v1, t_vector *v2);

// utils/print.c
void		print_vect(t_vector *vector);
void		print_ray(t_ray *ray);
void		print_sphere(t_sphere *sphere);

// utils/math_utils.c
float		calculate_discriminant(float a, float b, float c);
float		equation_result(float a, float b);
float		equation_minus_result(float a, float b,
									float discriminant);
float		equation_plus_result(float a, float b, float discriminant);

#endif
