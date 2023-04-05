/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_intensity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:16:10 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/05 16:58:11 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	minus_intensity(t_all *all, float *intensity, int y_start);
static void	plus_intensity(t_all *all, float *intensity, int y_start);
static void	cursor_intensity(t_all *all, float *intensity, int y_start);

/*
 * Draw intensity of a light in the menu
 */
void	display_intensity(t_all *all, float intensity, int y_start)
{
	char	*tmp;
	char	*to_print;

	tmp = ft_ftoa(intensity);
	to_print = ft_strjoin("intensity : ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 400, y_start);
	free(tmp);
	free(to_print);
}

/*
 * Draw and manage button for intensity in a light
 */
void	manage_intensity(t_all *all, float *intensity, int y_start)
{
	all->menu.cur_float.select = (*intensity) * 40.0f;
	minus_intensity(all, intensity, y_start);
	plus_intensity(all, intensity, y_start);
	cursor_intensity(all, intensity, y_start);
}

/*
 * Draw and manage minus button for one intensity
 */
static void	minus_intensity(t_all *all, float *intensity, int y_start)
{
	but_set_pos(&all->menu.but_minus, WIDTH - 160, y_start);
	if (*intensity == 0.0f)
		all->menu.but_minus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_minus))
		all->menu.but_minus.color = 0x999999FF;
	else
		all->menu.but_minus.color = 0x666666FF;
	if (*intensity > 0.0f && but_click(all, &all->menu.but_minus))
	{
		(*intensity) -= 0.1f;
		if (*intensity < 0.0f)
			*intensity = 0.0f;
		all->menu.cur_float.select = (*intensity) * 40.0f;
		all->draw_state = NEED_REDRAW;
	}
	but_draw(all, &all->menu.but_minus);
}

/*
 * Draw and manage plus button for one intensity
 */
static void	plus_intensity(t_all *all, float *intensity, int y_start)
{
	but_set_pos(&all->menu.but_plus, WIDTH - 140, y_start);
	if (*intensity == 1.0f)
		all->menu.but_plus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_plus))
		all->menu.but_plus.color = 0x999999FF;
	else
		all->menu.but_plus.color = 0x666666FF;
	if (*intensity < 1.0f && but_click(all, &all->menu.but_plus))
	{
		(*intensity) += 0.1f;
		if (*intensity > 1.0f)
			*intensity = 1.0f;
		all->menu.cur_float.select = (*intensity) * 40.0f;
		all->draw_state = NEED_REDRAW;
	}
	but_draw(all, &all->menu.but_plus);
}

/*
 * Draw and manage cursor for one intensity
 */
static void	cursor_intensity(t_all *all, float *intensity, int y_start)
{
	cur_set_pos(&all->menu.cur_float, WIDTH - 200, y_start);
	cur_tick(all, &all->menu.cur_float);
	if ((*intensity) * 40.0f != all->menu.cur_float.select)
	{
		*intensity = (float)all->menu.cur_float.select / 40.0f;
		all->draw_state = NEED_REDRAW;
	}
	cur_draw(all, &all->menu.cur_float);
}
