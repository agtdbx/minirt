/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_float_range.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:16:10 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/25 13:50:35 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	minus_float_range(t_all *all, float *float_range, int y_start,
				int x_gap);
static void	plus_float_range(t_all *all, float *float_range, int y_start,
				int x_gap);
static void	cursor_float_range(t_all *all, float *float_range, int y_start,
				int x_gap);

/*
 * Draw float_range of a light in the menu
 */
void	display_float_range(t_all *all, float float_range, int y_start,
			char *text)
{
	char	*tmp;
	char	*to_print;

	tmp = ft_ftoa(float_range);
	to_print = ft_strjoin(text, tmp);
	my_put_string(all, to_print, WIDTH - 400, y_start);
	free(tmp);
	free(to_print);
}

/*
 * Draw and manage button for float_range in a light
 */
void	manage_float_range(t_all *all, float *float_range, int y_start,
			char *text)
{
	int const	x_gap = (ft_strlen(text) + 9) * 10;

	all->menu.cur_float.select = (*float_range) * 40.0f;
	minus_float_range(all, float_range, y_start, x_gap);
	plus_float_range(all, float_range, y_start, x_gap);
	cursor_float_range(all, float_range, y_start, x_gap);
}

/*
 * Draw and manage minus button for one float_range
 */
static void	minus_float_range(t_all *all, float *float_range, int y_start,
				int x_gap)
{
	but_set_pos(&all->menu.but_minus, WIDTH - 360 + x_gap, y_start);
	if (*float_range == 0.0f)
		all->menu.but_minus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_minus))
		all->menu.but_minus.color = 0x999999FF;
	else
		all->menu.but_minus.color = 0x666666FF;
	if (*float_range > 0.0f && but_click(all, &all->menu.but_minus))
	{
		(*float_range) -= 0.1f;
		if (*float_range < 0.0f)
			*float_range = 0.0f;
		all->menu.cur_float.select = (*float_range) * 40.0f;
		all->draw_state = NEED_REDRAW;
	}
	but_draw(all, &all->menu.but_minus);
}

/*
 * Draw and manage plus button for one float_range
 */
static void	plus_float_range(t_all *all, float *float_range, int y_start,
				int x_gap)
{
	but_set_pos(&all->menu.but_plus, WIDTH - 340 + x_gap, y_start);
	if (*float_range == 1.0f)
		all->menu.but_plus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_plus))
		all->menu.but_plus.color = 0x999999FF;
	else
		all->menu.but_plus.color = 0x666666FF;
	if (*float_range < 1.0f && but_click(all, &all->menu.but_plus))
	{
		(*float_range) += 0.1f;
		if (*float_range > 1.0f)
			*float_range = 1.0f;
		all->menu.cur_float.select = (*float_range) * 40.0f;
		all->draw_state = NEED_REDRAW;
	}
	but_draw(all, &all->menu.but_plus);
}

/*
 * Draw and manage cursor for one float_range
 */
static void	cursor_float_range(t_all *all, float *float_range, int y_start,
				int x_gap)
{
	cur_set_pos(&all->menu.cur_float, WIDTH - 400 + x_gap, y_start);
	cur_tick(all, &all->menu.cur_float);
	if ((int)((*float_range) * 40.0f) != all->menu.cur_float.select)
	{
		*float_range = (float)all->menu.cur_float.select / 40.0f;
		all->draw_state = NEED_REDRAW;
	}
	cur_draw(all, &all->menu.cur_float);
}
