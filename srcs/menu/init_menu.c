/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:12:17 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/02 15:37:26 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_plus_minus(t_all *all);
static void	init_cursor(t_all *all);

void	init_menu(t_all *all)
{
	all->menu.id_obj_select = SELECT_NONE;
	all->menu.but_camera.x = WIDTH - 420;
	all->menu.but_camera.y = 50;
	all->menu.but_camera.width = 210;
	all->menu.but_camera.height = 40;
	all->menu.but_camera.text = "CAMERA";
	all->menu.but_camera.color = 0X666666FF;
	all->menu.but_ambiant_ligth.x = WIDTH - 210;
	all->menu.but_ambiant_ligth.y = 50;
	all->menu.but_ambiant_ligth.width = 210;
	all->menu.but_ambiant_ligth.height = 40;
	all->menu.but_ambiant_ligth.color = 0X666666FF;
	all->menu.but_ambiant_ligth.text = "AMBIANT LIGHT";
	init_plus_minus(all);
	init_cursor(all);
}

static void	init_plus_minus(t_all *all)
{
	all->menu.but_minus.x = WIDTH;
	all->menu.but_minus.y = 150;
	all->menu.but_minus.width = 20;
	all->menu.but_minus.height = 20;
	all->menu.but_minus.color = 0X666666FF;
	all->menu.but_minus.text = "-";
	all->menu.but_plus.x = WIDTH;
	all->menu.but_plus.y = 150;
	all->menu.but_plus.width = 20;
	all->menu.but_plus.height = 20;
	all->menu.but_plus.color = 0X666666FF;
	all->menu.but_plus.text = "+";
}

static void	init_cursor(t_all *all)
{
	all->menu.cur_fov.x = WIDTH - 300;
	all->menu.cur_fov.y = 220;
	all->menu.cur_fov.width = 180;
	all->menu.cur_fov.height = 20;
	all->menu.cur_fov.select = all->scene.camera.fov;
	all->menu.cur_color.x = WIDTH - 300;
	all->menu.cur_color.y = 220;
	all->menu.cur_color.width = 128;
	all->menu.cur_color.height = 20;
	all->menu.cur_color.select = 0;
	all->menu.cur_float.x = WIDTH - 300;
	all->menu.cur_float.y = 220;
	all->menu.cur_float.width = 40;
	all->menu.cur_float.height = 20;
	all->menu.cur_float.select = 0;
}
