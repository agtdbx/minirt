/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:57:01 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/06 12:08:17 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	minus_dir_axis(t_all *all, float *channel, int y);
static bool	plus_dir_axis(t_all *all, float *channel, int y);
static bool	cursor_dir_axis(t_all *all, float *channel, int y);

/*
 * Draw each direction axis in differents lines in the menu
 */
void	display_dir(t_all *all, t_vector *dir, int y_start)
{
	char	*tmp;
	char	*to_print;

	tmp = ft_ftoa(dir->x);
	to_print = ft_strjoin("direction : x ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 400, y_start);
	free(tmp);
	free(to_print);
	tmp = ft_ftoa(dir->y);
	to_print = ft_strjoin("y ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 280, y_start + 20);
	free(tmp);
	free(to_print);
	tmp = ft_ftoa(dir->z);
	to_print = ft_strjoin("z ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 280, y_start + 40);
	free(tmp);
	free(to_print);
}

/*
 * Draw and manage button for each direction axis in the menu
 */
bool	manage_dir(t_all *all, t_vector *dir, int y_start)
{
	bool		modify;

	all->menu.cur_float.select = (dir->x * 20.0f) + 20.0f;
	modify = minus_dir_axis(all, &dir->x, y_start);
	modify += plus_dir_axis(all, &dir->x, y_start);
	modify += cursor_dir_axis(all, &dir->x, y_start);
	all->menu.cur_float.select = (dir->y * 20.0f) + 20.0f;
	modify += minus_dir_axis(all, &dir->y, y_start + 20);
	modify += plus_dir_axis(all, &dir->y, y_start + 20);
	modify += cursor_dir_axis(all, &dir->y, y_start + 20);
	all->menu.cur_float.select = (dir->z * 20.0f) + 20.0f;
	modify += minus_dir_axis(all, &dir->z, y_start + 40);
	modify += plus_dir_axis(all, &dir->z, y_start + 40);
	modify += cursor_dir_axis(all, &dir->z, y_start + 40);
	return (modify);
}

/*
 * Draw and manage minus button for one direction axis
 */
static bool	minus_dir_axis(t_all *all, float *channel, int y)
{
	bool		modify;

	modify = false;
	but_set_pos(&all->menu.but_minus, WIDTH - 120, y);
	if (*channel == -1.0f)
		all->menu.but_minus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_minus))
		all->menu.but_minus.color = 0x999999FF;
	else
		all->menu.but_minus.color = 0x666666FF;
	if (*channel > -1.0f && but_click(all, &all->menu.but_minus))
	{
		(*channel) -= 0.1f;
		if (*channel < -1.0f)
			*channel = -1.0f;
		all->menu.cur_color.select = ((*channel) * 20.0f) + 20.0f;
		all->draw_state = NEED_REDRAW;
		modify = true;
	}
	but_draw(all, &all->menu.but_minus);
	return (modify);
}

/*
 * Draw and manage plus button for one direction axis
 */
static bool	plus_dir_axis(t_all *all, float *channel, int y)
{
	bool		modify;

	modify = false;
	but_set_pos(&all->menu.but_plus, WIDTH - 100, y);
	if (*channel == 1.0f)
		all->menu.but_plus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_plus))
		all->menu.but_plus.color = 0x999999FF;
	else
		all->menu.but_plus.color = 0x666666FF;
	if (*channel < 1.0f && but_click(all, &all->menu.but_plus))
	{
		(*channel) += 0.1f;
		if (*channel > 1.0f)
			*channel = 1.0f;
		all->menu.cur_color.select = ((*channel) * 20.0f) + 20.0f;
		all->draw_state = NEED_REDRAW;
		modify = true;
	}
	but_draw(all, &all->menu.but_plus);
	return (modify);
}

/*
 * Draw and manage scroll for one color channel
 */
static bool	cursor_dir_axis(t_all *all, float *channel, int y)
{
	bool		modify;

	modify = false;
	cur_set_pos(&all->menu.cur_float, WIDTH - 160, y);
	cur_tick(all, &all->menu.cur_float);
	if ((int)(((*channel) * 20.0f) + 20.0f) != all->menu.cur_float.select)
	{
		*channel = ((float)all->menu.cur_float.select - 20.0f) / 20.0f;
		all->draw_state = NEED_REDRAW;
		modify = true;
	}
	cur_draw(all, &all->menu.cur_float);
	return (modify);
}
