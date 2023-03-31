/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:14:50 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/31 16:46:23 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	draw_sphere(t_all *all, t_sphere *sphere);
static void	draw_plane(t_all *all, t_plane *plane);
static void	draw_cylinder(t_all *all, t_cylinder *cylinder);

void	check_tab_pressed(t_all *all, float const delta_time)
{
	static float	last_time = 0.0f;

	if (last_time > 0.0f)
	{
		last_time -= delta_time;
		if (last_time < 0.0f)
			last_time = 0.0f;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_TAB) && last_time == 0.0f)
	{
		if (all->show_menu)
			mlx_image_to_window(all->mlx, all->img, 0, 0);
		all->show_menu = !all->show_menu;
		last_time = 0.5f;
	}
}

void	draw_menu(t_all *all)
{
	int		x;
	int		y;
	t_rtlst	*obj;

	y = 0;
	while (y < HEIGHT)
	{
		x = WIDTH - 420;
		while (x < WIDTH)
		{
			if (x == WIDTH - 420 || x == WIDTH - 1
				|| y == 0 || y == HEIGHT - 1)
				mlx_put_pixel(all->img, x, y, 0XFFFFFFFF);
			else
				mlx_put_pixel(all->img, x, y, 0X333333FF);
			x++;
		}
		y++;
	}
	mlx_put_string(all->mlx, "MENU", WIDTH - 220, 10);
	obj = get_obj_by_index(all->scene.objects, all->id_obj_select);
	if (obj != NULL)
	{
		if (obj->type == SPHERE)
			draw_sphere(all, &obj->value.as_sphere);
		if (obj->type == PLANE)
			draw_plane(all, &obj->value.as_plane);
		if (obj->type == CYLINDER)
			draw_cylinder(all, &obj->value.as_cylinder);
	}
}

static void	draw_sphere(t_all *all, t_sphere *sphere)
{
	(void)all;
	(void)sphere;
	mlx_put_string(all->mlx, "SPHERE", WIDTH - 220, 50);
}

static void	draw_plane(t_all *all, t_plane *plane)
{
	(void)all;
	(void)plane;
	mlx_put_string(all->mlx, "PLANE", WIDTH - 220, 50);
}

static void	draw_cylinder(t_all *all, t_cylinder *cylinder)
{
	(void)all;
	(void)cylinder;
	mlx_put_string(all->mlx, "CYLINDER", WIDTH - 220, 50);
}
