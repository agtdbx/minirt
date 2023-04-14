/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:22:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/14 12:07:45 by aderouba         ###   ########.fr       */
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
# define HEIGHT 995

# define WIDTH_DIV_2 960
# define HEIGHT_DIV_2 497.5

# define LIGHT_DIFFUSE_RADIUS 100.0f

# define MAX_REFLECT 4

// Define for pre-calculate value
# define PI 3.141592
# define PI_DIV_180 0.017453
# define PI_DIV_360 0.008726

// Define for rotate parameter
# define ROTATE_AROUND_X 'x'
# define ROTATE_AROUND_Y 'y'
# define ROTATE_AROUND_Z 'z'

// Define for objet selected
# define SELECT_NONE -1
# define SELECT_CAMERA -2
# define SELECT_AMBIANT_LIGHT -3
# define SELECT_LIGHT -4

// Define for intensty of ambiant, diffuse and specular
# define REFLECTION_AMBIANT_RATIO 0.2f
# define REFLECTION_DIFFUSE_RATIO 0.5f
# define REFLECTION_SPECULAR_RATIO 0.3f

////////////////////////////////////////////////////////////////////////////////
// STRUCTS

// Draw state enem
typedef enum e_draw_state
{
	DRAW_PIXELS,
	NEED_REDRAW,
	DRAW_TEXT
}	t_draw_state;

// Color struct
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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
	float		shininess_intensity;
	float		reflexion_intensity;
	t_color		color;
	int			id;
}	t_sphere;

// Plane struct
typedef struct s_plane
{
	t_vector	origin;
	t_vector	normal;
	t_vector	rev_normal;
	t_color		color;
	float		shininess_intensity;
	float		reflexion_intensity;
	int			id;
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
	float		shininess_intensity;
	float		reflexion_intensity;
	t_color		color;
	int			id;
}	t_cylinder;

// Intersect result struct
typedef struct s_intersect_ret
{
	t_vector	nrm;
	t_color		color;
	float		dst;
	float		intensity_r;
	float		intensity_g;
	float		intensity_b;
	float		shininess_intensity;
	float		reflexion_intensity;
	int			id;
}	t_intersect_ret;

// Camera Struct
typedef struct s_camera
{
	t_vector	pos;
	t_vector	orientation;
	t_vector	basis[3];
	int			fov;
	float		len;
}	t_camera;

// Light Struct
typedef struct s_light
{
	t_vector	pos;
	float		brightness;
	float		intensity_r;
	float		intensity_g;
	float		intensity_b;
	t_color		color;
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
	int				id;
}	t_rtlst;

// Scene Struct
typedef struct s_scene
{
	t_light		ambient_light;
	int			ppr;
	t_camera	camera;
	t_light		light;
	t_rtlst		*objects;
}	t_scene;

// Button Struct
typedef struct s_button
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
	char	*text;
}	t_button;

// Cursor Struct
typedef struct s_cursor
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		select;
}	t_cursor;

// Scene Struct
typedef struct s_menu
{
	t_button	but_camera;
	t_button	but_ambiant_ligth;
	t_button	but_ligth;
	t_button	but_minus;
	t_button	but_plus;
	t_cursor	cur_fov;
	t_cursor	cur_color;
	t_cursor	cur_float;
	int			id_obj_select;
}	t_menu;

// Mouse struct
typedef struct s_mouse
{
	bool	pressed;
	int		x;
	int		y;
	int		tab_x;
	int		tab_y;
}	t_mouse;

// Image lst
typedef struct s_imglst
{
	mlx_image_t		*img;
	struct s_imglst	*next;
}	t_imglst;

// Main struct
typedef struct s_all
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_scene			scene;
	t_menu			menu;
	t_ray			**ray_tab;
	double			last_time;
	int				**colors_tab;
	bool			show_menu;
	t_draw_state	draw_state;
	t_mouse			mouse;
	t_imglst		*text_imgs;
}	t_all;

////////////////////////////////////////////////////////////////////////////////
// FILES

// main.c
void		hook(void *param);
int			main(int argc, char **argv);

/*====================================OBJECT==================================*/

// objets/sphere.c
t_sphere	create_sphere(t_vector origin, float diameter, t_color color);
void		intersect_sphere(t_sphere *sphere, t_ray *ray,
				t_intersect_ret *intersect_ret);

// objets/plane.c
t_plane		create_plane(t_vector origin, t_vector normal, t_color color);
void		intersect_plane(t_plane *plane, t_ray *ray,
				t_intersect_ret *intersect_ret);

// objets/cylinder.c
t_cylinder	create_cylinder(t_vector origin, t_vector axis, float size[2],
				t_color color);
void		intersect_cylinder(t_cylinder *cylinder, t_ray *ray,
				t_intersect_ret *intersect_ret);

// objets/camera.c
void		get_screen_basis(t_vector const *camera, t_vector ret_basis[2],
				int ppr);
void		fill_tab_ray(t_ray **ray_tab, t_scene *scene,
				int number_ray, int number_line);

// objets/space_operations.c
void		translate(t_vector *vector, float x, float y, float z);
void		absolute_rotate(t_vector *vector, float angle, char axis);
void		relative_rotate(t_vector *restrict vect,
				t_vector const *restrict axis, float angle);

void		my_vect_cpy(t_vector *restrict dst, t_vector const *restrict src);

// objets/camera_operation.c
void		camera_translations(t_all *all, float delta_time);
void		camera_rotations(t_all *all, float delta_time);

/*=====================================DRAW===================================*/

// image/ppr.c
void		ppr_gestion(t_all *all, float delta_time);

// image/draw.c
int			get_rgb(int r, int g, int b);
void		draw_pixels(t_all *all, int x, int y, int color);
void		draw_result(t_all *all, t_intersect_ret *res, int x, int y);

// image/calculate_image.c
void		calculate_image(t_all *all);

// image/ray_tab.c
void		free_ray_tab(t_ray **ray_tab, int max_alloc);
t_ray		**alloc_ray_tab(void);

// image/antialiasing.c
void		apply_antialiasing(t_all *all);

// image/color_tab.c
void		free_color_tab(int **color_tab, int max_alloc);
int			**alloc_color_tab(void);

// image/compute_pixel.c
void		compute_pixel(t_all *all, t_intersect_ret *res, int x, int y);

// image/incremente_intensity.c
void		incremente_intensity(t_intersect_ret *res, t_light const *light,
				float const reflection_ratio);

// image/compute_light.c
void		compute_light(t_all *all, t_intersect_ret *res, t_ray *ray,
				int reflect);

// image/add_diffuse_intensity.c
bool		add_diffuse_intensity(t_all *all, t_intersect_ret *res,
				t_light const *light, t_vector const *pixel_pos);

// image/add_specular_intensity.c
void		add_specular_intensity(t_all *all, t_intersect_ret *res,
				t_light const *light, t_vector const *pixel_pos);

// image/mirror_reflection.c
void		mirror_reflection(t_all *all, t_intersect_ret *res,
				t_ray const *ray, int reflect);

/*=====================================MENU===================================*/

// image/buttons.c
void		but_set_pos(t_button *but, int const x, int const y);
void		but_draw(t_all *all, t_button const *but);
bool		but_over(t_all *all, t_button *but);
bool		but_click(t_all *all, t_button *but);

// image/cursor.c
void		cur_set_pos(t_cursor *cur, int const x, int const y);
void		cur_draw(t_all *all, t_cursor const *cur);
void		cur_tick(t_all *all, t_cursor *cur);

// menu/menu.c
void		check_tab_pressed(t_all *all, float const delta_time);
void		init_menu(t_all *all);
void		draw_menu(t_all *all);

// menu/display_camera.c
void		display_camera(t_all *all, t_camera *camera);

// menu/display_ambiant_light.c
void		display_ambiant_light(t_all *all, t_light *ambiant_light);

// menu/display_light.c
void		display_light(t_all *all, t_light *light);

// menu/display_sphere.c
void		display_sphere(t_all *all, t_sphere *sphere);

// menu/display_plane.c
void		display_plane(t_all *all, t_plane *plane);

// menu/display_cylinder.c
void		display_cylinder(t_all *all, t_cylinder *cylinder);

// menu/display_color.c
void		display_color(t_all *all, t_color *color, int y_start);
bool		manage_color(t_all *all, t_color *color, int y_start);

// menu/display_dir.c
void		display_dir(t_all *all, t_vector *dir, int y_start);
bool		manage_dir(t_all *all, t_vector *dir, int y_start);

// menu/display_pos.c
void		display_pos(t_all *all, t_vector *pos, int y_start);
bool		manage_pos(t_all *all, t_vector *pos, int y_start);

// menu/display_float.c
void		display_float(t_all *all, float number, int y_start, char *text);
bool		manage_float(t_all *all, float *number, int y_start, char *text);

// menu/display_float_range.c
void		display_float_range(t_all *all, float float_range, int y_start,
				char *text);
void		manage_float_range(t_all *all, float *float_range, int y_start,
				char *text);

// menu/my_put_string.c
void		my_put_string(t_all *all, char *text, int x, int y);

/*====================================PARSING=================================*/

// parsing/parse_file.c
t_result	parse_file(char const *filename, t_scene *ret_scene);

// parsing/parse_lights.c
t_result	parse_ambient_light(t_scene *ret_scene);
t_result	parse_light(t_scene *ret_scene);

// parsing/parse_objects.c
t_result	parse_camera(t_scene *ret_scene);
t_result	parse_sphere(t_scene *ret_scene);
t_result	parse_plane(t_scene *ret_scene);
t_result	parse_cylinder(t_scene *ret_scene);

// parsing/parse_color.c
t_result	parse_color(char *rgb_str, t_color *ret_color);

// parsing/parse_vec.c
t_result	parse_vec(char *xyz_str, t_vector *ret_vec);

// parsing/parse_vec.c
t_result	parse_direction(char *xyz_str, t_vector *ret_vec);

// parsing/parse_float.c
t_result	parse_float(char const *nptr, float *ret_float);

/*====================================MATHS===================================*/

// maths/compute_screen_basis.c
void		compute_screen_basis(t_camera *ret_cam);

// maths/is_xyz_in_range.c
bool		is_xyz_in_range(t_vector const *vec, float min, float max);

/*====================================UTILS===================================*/

// utils/vector.c
void		fill_vec(t_vector *vec, float const x, float const y,
				float const z);
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
t_rtlst		*rtlst_new(t_rtlst_t type, t_rtlst_v value, int id);
void		rtlst_add_back(t_rtlst **rtlst, t_rtlst *new);
void		rtlst_free(t_rtlst **rtlst);
t_rtlst		*get_obj_by_index(t_rtlst *rtlst, int id);

// utils/imglst.c
t_imglst	*imglst_new(mlx_image_t *img);
void		imglst_add_back(t_imglst **imglst, t_imglst *new);
void		imglst_clear(t_all *all, t_imglst **imglst);

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
t_vector	get_point_on_ray(t_ray const *ray, float const dist);

// utils/number.c
bool		is_int(char const *str);
bool		is_float(char const *str);

// utils/string.c
char		*ft_strtok_r(char *str, char const *sep, char **saveptr);
char		*ft_strtok(char *str, char const *sep);

// utils/dst_and_nrm.c
void		init_intersect_ret(t_intersect_ret *to_init);

#endif
