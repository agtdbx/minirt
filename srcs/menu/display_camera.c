/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:38:57 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/14 13:13:25 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	minus_fov(t_all *all, t_camera *camera);
static void	plus_fov(t_all *all, t_camera *camera);
static void	cursor_fov(t_all *all, t_camera *camera);
static char	*display_const_vec(char *text, t_vector *vec);

/*
 * Draw and manage the camera's informations into the menu
 */
void	display_camera(t_all *all, t_camera *camera)
{
	char	*tmp;
	char	*to_print;

	minus_fov(all, camera);
	plus_fov(all, camera);
	cursor_fov(all, camera);
	if (all->draw_state != DRAW_TEXT)
		return ;
	my_put_string(all, "CAMERA", WIDTH - 240, 100);
	to_print = display_const_vec("pos : ", &camera->pos);
	my_put_string(all, to_print, WIDTH - 400, 140);
	free(to_print);
	to_print = display_const_vec("dir : ", &camera->basis[2]);
	my_put_string(all, to_print, WIDTH - 400, 180);
	free(to_print);
	tmp = ft_itoa(camera->fov);
	to_print = ft_strjoin("fov : ", tmp);
	my_put_string(all, to_print, WIDTH - 400, 220);
	free(tmp);
	free(to_print);
}

/*
 * Draw and manage the minus button for the fov of the camera
 */
static void	minus_fov(t_all *all, t_camera *camera)
{
	float	len;

	but_set_pos(&all->menu.but_minus, WIDTH - 120, 220);
	if (camera->fov == 0)
		all->menu.but_minus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_minus))
		all->menu.but_minus.color = 0x999999FF;
	else
		all->menu.but_minus.color = 0x666666FF;
	if (camera->fov > 0 && but_click(all, &all->menu.but_minus))
	{
		camera->fov--;
		all->menu.cur_fov.select = camera->fov;
		len = WIDTH / (tan(camera->fov * PI_DIV_360) * 2.0f);
		dup_vec(&all->scene.camera.orientation, &all->scene.camera.basis[2]);
		multiply_vec_number(&all->scene.camera.orientation, len);
		all->draw_state = NEED_REDRAW;
	}
	but_draw(all, &all->menu.but_minus);
}

/*
 * Draw and manage the plus button for the fov of the camera
 */
static void	plus_fov(t_all *all, t_camera *camera)
{
	float	len;

	but_set_pos(&all->menu.but_plus, WIDTH - 100, 220);
	if (camera->fov == 180)
		all->menu.but_plus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_plus))
		all->menu.but_plus.color = 0x999999FF;
	else
		all->menu.but_plus.color = 0x666666FF;
	if (camera->fov < 180 && but_click(all, &all->menu.but_plus))
	{
		camera->fov++;
		all->menu.cur_fov.select = camera->fov;
		len = WIDTH / (tan(camera->fov * PI_DIV_360) * 2.0f);
		dup_vec(&all->scene.camera.orientation, &all->scene.camera.basis[2]);
		multiply_vec_number(&all->scene.camera.orientation, len);
		all->draw_state = NEED_REDRAW;
	}
	but_draw(all, &all->menu.but_plus);
}

/*
 * Draw and manage the cursor for the fov of the camera
 */
static void	cursor_fov(t_all *all, t_camera *camera)
{
	cur_tick(all, &all->menu.cur_fov);
	if (camera->fov != all->menu.cur_fov.select)
	{
		camera->fov = all->menu.cur_fov.select;
		camera->len = WIDTH_DIV_2 / tan(camera->fov * PI_DIV_360);
		dup_vec(&all->scene.camera.orientation, &all->scene.camera.basis[2]);
		multiply_vec_number(&all->scene.camera.orientation, camera->len);
		all->draw_state = NEED_REDRAW;
	}
	cur_draw(all, &all->menu.cur_fov);
}

/*
 * Draw a vector which can't be modify in the menu
 */
static char	*display_const_vec(char *text, t_vector *vec)
{
	char	*tmp;
	char	*res;

	res = ft_strdup(text);
	tmp = ft_ftoa(vec->x);
	res = ft_strjoin_free_1st_p(res, tmp);
	tmp = ft_ftoa(vec->y);
	res = ft_strsuperjoin_free_1st_p(res, tmp, ", ");
	free(tmp);
	tmp = ft_ftoa(vec->z);
	res = ft_strsuperjoin_free_1st_p(res, tmp, ", ");
	free(tmp);
	return (res);
}
