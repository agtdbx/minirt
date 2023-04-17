/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:57:01 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/17 16:13:17 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	minus_color_channel(t_all *all, int *channel, int y);
static bool	plus_color_channel(t_all *all, int *channel, int y);
static bool	cursor_color_channel(t_all *all, int *channel, int y);

/*
 * Draw each color channel in differents lines in the menu
 */
void	display_color(t_all *all, t_color *color, int y_start)
{
	char	*tmp;
	char	*to_print;

	tmp = ft_itoa(color->r);
	to_print = ft_strjoin("color : r ", tmp);
	my_put_string(all, to_print, WIDTH - 400, y_start);
	free(tmp);
	free(to_print);
	tmp = ft_itoa(color->g);
	to_print = ft_strjoin("g ", tmp);
	my_put_string(all, to_print, WIDTH - 320, y_start + 20);
	free(tmp);
	free(to_print);
	tmp = ft_itoa(color->b);
	to_print = ft_strjoin("b ", tmp);
	my_put_string(all, to_print, WIDTH - 320, y_start + 40);
	free(tmp);
	free(to_print);
}

/*
 * Draw and manage button for each color channel in the menu
 */
bool	manage_color(t_all *all, t_color *color, int y_start)
{
	bool	modify;

	all->menu.cur_color.select = color->r / 2;
	modify = minus_color_channel(all, &color->r, y_start);
	modify += plus_color_channel(all, &color->r, y_start);
	modify += cursor_color_channel(all, &color->r, y_start);
	all->menu.cur_color.select = color->g / 2;
	modify += minus_color_channel(all, &color->g, y_start + 20);
	modify += plus_color_channel(all, &color->g, y_start + 20);
	modify += cursor_color_channel(all, &color->g, y_start + 20);
	all->menu.cur_color.select = color->b / 2;
	modify += minus_color_channel(all, &color->b, y_start + 40);
	modify += plus_color_channel(all, &color->b, y_start + 40);
	modify += cursor_color_channel(all, &color->b, y_start + 40);
	return (modify);
}

/*
 * Draw and manage minus button for one color channel
 */
static bool	minus_color_channel(t_all *all, int *channel, int y)
{
	bool	modify;

	modify = false;
	but_set_pos(&all->menu.but_minus, WIDTH - 132, y);
	if (*channel == 0)
		all->menu.but_minus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_minus))
		all->menu.but_minus.color = 0x999999FF;
	else
		all->menu.but_minus.color = 0x666666FF;
	if (*channel > 0 && but_click(all, &all->menu.but_minus))
	{
		(*channel)--;
		all->menu.cur_color.select = (*channel) / 2;
		all->draw_state = NEED_REDRAW;
		modify = true;
	}
	but_draw(all, &all->menu.but_minus);
	return (modify);
}

/*
 * Draw and manage plus button for one color channel
 */
static bool	plus_color_channel(t_all *all, int *channel, int y)
{
	bool	modify;

	modify = false;
	but_set_pos(&all->menu.but_plus, WIDTH - 112, y);
	if (*channel == 255)
		all->menu.but_plus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_plus))
		all->menu.but_plus.color = 0x999999FF;
	else
		all->menu.but_plus.color = 0x666666FF;
	if (*channel < 255 && but_click(all, &all->menu.but_plus))
	{
		(*channel)++;
		all->menu.cur_color.select = (*channel) / 2;
		all->draw_state = NEED_REDRAW;
		modify = true;
	}
	but_draw(all, &all->menu.but_plus);
	return (modify);
}

/*
 * Draw and manage scroll for one color channel
 */
static bool	cursor_color_channel(t_all *all, int *channel, int y)
{
	bool	modify;

	modify = false;
	cur_set_pos(&all->menu.cur_color, WIDTH - 260, y);
	cur_tick(all, &all->menu.cur_color);
	if ((*channel) / 2 != all->menu.cur_color.select)
	{
		*channel = all->menu.cur_color.select * 2;
		if (*channel > 255)
			*channel = 255;
		all->draw_state = NEED_REDRAW;
		modify = true;
	}
	cur_draw(all, &all->menu.cur_color);
	return (modify);
}
