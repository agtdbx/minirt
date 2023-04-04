/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:14:50 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/04 15:37:01 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	display_selected(t_all *all);
static void	draw_but_color(t_all *all, t_button *but, int check);

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
		all->need_draw = true;
		all->show_menu = !all->show_menu;
		last_time = 0.5f;
	}
}

void	init_menu(t_all *all)
{
	all->menu.id_obj_select = SELECT_NONE;

	// Camera button
	all->menu.but_camera.x = WIDTH - 420;
	all->menu.but_camera.y = 50;
	all->menu.but_camera.width = 140;
	all->menu.but_camera.height = 40;
	all->menu.but_camera.text = "CAMERA";
	all->menu.but_camera.color = 0X666666FF;

	// Camera ambiant light
	all->menu.but_ambiant_ligth.x = WIDTH - 280;
	all->menu.but_ambiant_ligth.y = 50;
	all->menu.but_ambiant_ligth.width = 140;
	all->menu.but_ambiant_ligth.height = 40;
	all->menu.but_ambiant_ligth.color = 0X666666FF;
	all->menu.but_ambiant_ligth.text = "AMBIANT LIGHT";

	// Camera light
	all->menu.but_ligth.x = WIDTH - 140;
	all->menu.but_ligth.y = 50;
	all->menu.but_ligth.width = 140;
	all->menu.but_ligth.height = 40;
	all->menu.but_ligth.color = 0X666666FF;
	all->menu.but_ligth.text = "LIGHT";

	// Minus
	all->menu.but_minus.x = WIDTH;
	all->menu.but_minus.y = 150;
	all->menu.but_minus.width = 20;
	all->menu.but_minus.height = 20;
	all->menu.but_minus.color = 0X666666FF;
	all->menu.but_minus.text = "-";

	// Plus
	all->menu.but_plus.x = WIDTH;
	all->menu.but_plus.y = 150;
	all->menu.but_plus.width = 20;
	all->menu.but_plus.height = 20;
	all->menu.but_plus.color = 0X666666FF;
	all->menu.but_plus.text = "+";

	// fov cursor
	all->menu.cur_fov.x = WIDTH - 300;
	all->menu.cur_fov.y = 220;
	all->menu.cur_fov.width = 180;
	all->menu.cur_fov.height = 20;
	all->menu.cur_fov.select = all->scene.camera.fov;

	// color cursor
	all->menu.cur_color.x = WIDTH - 300;
	all->menu.cur_color.y = 220;
	all->menu.cur_color.width = 128;
	all->menu.cur_color.height = 20;
	all->menu.cur_color.select = 0;

	// float cursor
	all->menu.cur_float.x = WIDTH - 300;
	all->menu.cur_float.y = 220;
	all->menu.cur_float.width = 40;
	all->menu.cur_float.height = 20;
	all->menu.cur_float.select = 0;
}

void	draw_menu(t_all *all)
{
	int		x;
	int		y;

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
	if (but_click(all, &all->menu.but_camera))
	{
		all->menu.id_obj_select = SELECT_CAMERA;
		all->need_draw = true;
	}
	if (but_click(all, &all->menu.but_ambiant_ligth))
	{
		all->menu.id_obj_select = SELECT_AMBIANT_LIGHT;
		all->need_draw = true;
	}
	if (but_click(all, &all->menu.but_ligth))
	{
		all->menu.id_obj_select = SELECT_LIGHT;
		all->need_draw = true;
	}

	display_selected(all);

	draw_but_color(all, &all->menu.but_camera, SELECT_CAMERA);
	draw_but_color(all, &all->menu.but_ambiant_ligth, SELECT_AMBIANT_LIGHT);
	draw_but_color(all, &all->menu.but_ligth, SELECT_LIGHT);
}

static void	display_selected(t_all *all)
{
	t_rtlst	*obj;

	if (all->text_draw)
		mlx_put_string(all->mlx, "MENU", WIDTH - 230, 10);
	if (all->menu.id_obj_select == SELECT_CAMERA)
		display_camera(all, &all->scene.camera);
	else if (all->menu.id_obj_select == SELECT_AMBIANT_LIGHT)
		display_ambiant_light(all, &all->scene.ambient_light);
	else if (all->menu.id_obj_select == SELECT_LIGHT)
		display_light(all, &all->scene.light);
	else
	{
		obj = get_obj_by_index(all->scene.objects, all->menu.id_obj_select);
		if (obj != NULL)
		{
			if (obj->type == SPHERE)
				display_sphere(all, &obj->value.as_sphere);
			if (obj->type == PLANE)
				display_plane(all, &obj->value.as_plane);
			if (obj->type == CYLINDER)
				display_cylinder(all, &obj->value.as_cylinder);
		}
		else if (all->text_draw)
			mlx_put_string(all->mlx, "NONE", WIDTH - 230, 100);
	}
}

static void	draw_but_color(t_all *all, t_button *but, int check)
{
	if (all->menu.id_obj_select == check)
		but->color = 0X333333FF;
	else if (but_over(all, but))
		but->color = 0x999999FF;
	else
		but->color = 0x666666FF;
	but_draw(all, but);
}
