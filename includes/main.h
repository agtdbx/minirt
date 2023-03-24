/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:22:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/24 14:50:17 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <memory.h>
# include <math.h>
# include <fcntl.h>

# include "MLX42/MLX42.h"
# include "libft.h"

# define WIDTH 1920
# define HEIGHT 1080

// Define for pre-calculate value
# define PI 3.141592
# define PI_DIV_180 0.017453
# define PI_DIV_360 0.008726

// Define for rotate parameter
# define ROTATE_AROUND_X 'x'
# define ROTATE_AROUND_Y 'y'
# define ROTATE_AROUND_Z 'z'

////////////////////////////////////////////////////////////////////////////////
// STRUCTS

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
	int			color;
}	t_dst_and_nrm;

// Camera Struct
typedef struct s_camera
{
	t_vector	pos;
	t_vector	orientation;
	t_vector	basis[3];
	int			fov;
}	t_camera;

// Light Struct
typedef struct s_light
{
	t_vector	pos;
	float		brightness;
	int			color;
}	t_light;

// Object type
typedef enum e_rtlst_t
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_rtlst_t;

// Object union
typedef union u_rtlst_v
{
	t_sphere	as_sphere;
	t_plane		as_plane;
	t_cylinder	as_cylinder;
}	t_rtlst_v;

// Object list
typedef struct s_rtlst
{
	t_rtlst_t		type;
	t_rtlst_v		value;
	struct s_rtlst	*next;
}	t_rtlst;

// Scene Struct
typedef struct s_scene
{
	float		al_intensity;
	int			al_color;
	int			ppr;
	t_camera	camera;
	t_light		light;
	t_rtlst		*objects;
}	t_scene;

// Main struct
typedef struct s_all
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
	t_ray		**ray_tab;
	double		last_time;
	int			colors_tab[HEIGHT][WIDTH];
}	t_all;

////////////////////////////////////////////////////////////////////////////////
// FILES

// main.c
void		hook(void *param);
int			main(int argc, char **argv);

/*====================================OBJECT==================================*/

// objets/sphere.c
t_sphere	create_sphere(t_vector origin, float diameter, int color);
void		intersect_sphere(t_sphere *sphere, t_ray *ray,
				t_dst_and_nrm *dst_nrm);

// objets/plane.c
t_plane		create_plane(t_vector origin, t_vector normal, int color);
void		intersect_plane(t_plane *plane, t_ray *ray,
				t_dst_and_nrm *dst_nrm);

// objets/cylinder.c
t_cylinder	create_cylinder(t_vector origin, t_vector axis, float size[2],
				int color);
void		intersect_cylinder(t_cylinder *cylinder, t_ray *ray,
				t_dst_and_nrm *dst_nrm);

// objets/camera.c
void		get_screen_basis(t_vector const *camera, t_vector ret_basis[2],
				int ppr);
void		fill_tab_ray(t_ray **ray_tab, t_scene *scene,
				int number_ray, int number_line);

// objets/space_operations.c
void		translate(t_vector *vector, float x, float y, float z);
void		absolute_rotate(t_vector *vector, float angle, char axis);
void		my_rot_around(t_vector *restrict vect,
				t_vector const *restrict axis, float angle);

// objets/camera_operation.c
void		camera_translations(t_all *all, float delta_time);
void		camera_rotations(t_all *all, float delta_time);

/*=====================================DRAW===================================*/

//image/draw.c
int			get_rgb(int r, int g, int b);
void		draw(t_all *all);

//image/ray_tab.c
void		free_ray_tab(t_ray **ray_tab, int max_alloc);
t_ray		**alloc_ray_tab(void);

//image/antialiasing.c
void		apply_antialiasing(t_all *all);

/*====================================PARSING=================================*/

// parsing/parse_file.c
t_scene		parse_file(char *filename);

// parsing/parse_lights.c
bool		parse_ambient_light(t_scene *scene);
bool		parse_light(t_scene *scene);

// parsing/parse_objects.c
bool		parse_camera(t_scene *scene);
bool		parse_sphere(t_scene *scene);
bool		parse_plane(t_scene *scene);
bool		parse_cylinder(t_scene *scene);

/*====================================UTILS===================================*/

// utils/vector.c
void		fill_vec(t_vector *vec, float const x, float const y, float const z);
void		dup_vec(t_vector *vec, t_vector const *vec_to_dup);
float		get_length_vec(t_vector *vec);
void		normalize_vec(t_vector *vec);
void		multiply_vec_number(t_vector *vec, float const number);
void		add_vec_vec(t_vector *vec, t_vector const *vec_to_add);
void		sub_vec_vec(t_vector *vec, t_vector const *vec_to_sub);
float		dot_product(t_vector const *v1, t_vector const *v2);
void		cross_product(t_vector const *v1, t_vector const *v2,
				t_vector *vec_res);
void		get_normals_of_vect(t_vector const *vect, t_vector nrm[2]);

// utils/rtlst.c
t_rtlst		*rtlst_new(t_rtlst_t type, t_rtlst_v value);
void		rtlst_add_back(t_rtlst **rtlst, t_rtlst *new);
void		rtlst_free(t_rtlst **rtlst);

// utils/print.c
void		print_vect(t_vector *vector);
void		print_ray(t_ray *ray);
void		print_sphere(t_sphere *sphere);
void		print_plane(t_plane *plane);
void		print_cylinder(t_cylinder *cylinder);
void		print_ambiant_light(t_scene *scene);
void		print_camera(t_scene *scene);
void		print_light(t_scene *scene);
void		print_rtlst(t_rtlst *rtlst);

// utils/math_utils.c
float		solve_quadratic(float a, float b, float c);
t_vector	get_point_on_ray(t_ray *ray, float dist);

// utils/number.c
bool		is_int(char *str);
bool		is_float(char *str);

// utils/string.c
char		*ft_strtok_r(char *str, char const *sep, char **saveptr);
char		*ft_strtok(char *str, char const *sep);

// utils/parse_utils.c
int			parse_color(char *part);
bool		parse_vector(char *part, float *nbs, float min, float max);

#endif
