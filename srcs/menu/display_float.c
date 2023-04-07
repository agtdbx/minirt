/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:16:10 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/07 16:40:21 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	minus_float_axis(t_all *all, float *number, int const y,
				int const x_gap);
static bool	plus_float_axis(t_all *all, float *number, int const y,
				int const x_gap);

/*
 * Draw float with text before in the menu
 */
void	display_float(t_all *all, float number, int y_start, char *text)
{
	char	*tmp;
	char	*to_print;

	tmp = ft_ftoa(number);
	to_print = ft_strjoin(text, tmp);
	my_put_string(all, to_print, WIDTH - 400, y_start);
	free(tmp);
	free(to_print);
}

/*
 * Draw and manage button for one float in the menu
 */
bool	manage_float(t_all *all, float *number, int y_start, char *text)
{
	int const	x_gap = (ft_strlen(text) + 9) * 10;
	bool		modify;

	modify = minus_float_axis(all, number, y_start, x_gap);
	modify += plus_float_axis(all, number, y_start, x_gap);
	return (modify);
}

/*
 * Draw and manage minus button for one float
 */
static bool	minus_float_axis(t_all *all, float *number, int const y,
	int const x_gap)
{
	bool		modify;

	modify = false;
	but_set_pos(&all->menu.but_minus, WIDTH - 400 + x_gap, y);
	if (*number == 0.1f)
		all->menu.but_minus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_minus))
		all->menu.but_minus.color = 0x999999FF;
	else
		all->menu.but_minus.color = 0x666666FF;
	if (*number > 0.1f && but_click(all, &all->menu.but_minus))
	{
		(*number) -= 0.1f;
		all->draw_state = NEED_REDRAW;
		modify = true;
	}
	but_draw(all, &all->menu.but_minus);
	return (modify);
}

/*
 * Draw and manage plus button for one float
 */
static bool	plus_float_axis(t_all *all, float *number, int y, int x_gap)
{
	bool	modify;

	modify = false;
	but_set_pos(&all->menu.but_plus, WIDTH - 380 + x_gap, y);
	if (but_over(all, &all->menu.but_plus))
		all->menu.but_plus.color = 0x999999FF;
	else
		all->menu.but_plus.color = 0x666666FF;
	if (but_click(all, &all->menu.but_plus))
	{
		(*number) += 0.1f;
		all->draw_state = NEED_REDRAW;
		modify = true;
	}
	but_draw(all, &all->menu.but_plus);
	return (modify);
}
