/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:14:50 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/19 13:12:47 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	check_button_click(t_all *all);
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
		all->draw_state = NEED_REDRAW;
		all->show_menu = !all->show_menu;
		last_time = 0.5f;
	}
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
	check_button_click(all);
	display_selected(all);
	draw_but_color(all, &all->menu.but_camera, SELECT_CAMERA);
	draw_but_color(all, &all->menu.but_ambiant_ligth, SELECT_AMBIANT_LIGHT);
}

static void	check_button_click(t_all *all)
{
	if (but_click(all, &all->menu.but_camera))
	{
		all->menu.id_obj_select = SELECT_CAMERA;
		all->draw_state = NEED_REDRAW;
	}
	if (but_click(all, &all->menu.but_ambiant_ligth))
	{
		all->menu.id_obj_select = SELECT_AMBIANT_LIGHT;
		all->draw_state = NEED_REDRAW;
	}
}

static void	display_selected(t_all *all)
{
	t_rtlst	*obj;
	t_light	*light;

	if (all->draw_state == DRAW_TEXT)
		my_put_string(all, "MENU", WIDTH - 230, 10);
	if (all->menu.id_obj_select == SELECT_CAMERA)
		display_camera(all, &all->scene.camera);
	else if (all->menu.id_obj_select == SELECT_AMBIANT_LIGHT)
		display_ambiant_light(all, &all->scene.ambient_light);
	else if (all->menu.id_obj_select < -3)
	{
		light = all->scene.lights;
		while (light)
		{
			if (all->menu.id_obj_select == light->id)
			{
				display_light(all, light);
				break ;
			}
			light = light->next;
		}
	}
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
		else if (all->draw_state == DRAW_TEXT)
			my_put_string(all, "NONE", WIDTH - 230, 100);
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
