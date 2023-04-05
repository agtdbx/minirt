/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:57:01 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/05 12:12:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	minus_pos_axis(t_all *all, float *channel, int y);
static void	plus_pos_axis(t_all *all, float *channel, int y);

/*
 * Draw each position axis in differents lines in the menu
 */
void	display_pos(t_all *all, t_vector *pos, int y_start)
{
	char	*tmp;
	char	*to_print;

	tmp = ft_ftoa(pos->x);
	to_print = ft_strjoin("position : x ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 400, y_start);
	free(tmp);
	free(to_print);

	tmp = ft_ftoa(pos->y);
	to_print = ft_strjoin("y ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 290, y_start + 20);
	free(tmp);
	free(to_print);

	tmp = ft_ftoa(pos->z);
	to_print = ft_strjoin("z ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 290, y_start + 40);
	free(tmp);
	free(to_print);
}

/*
 * Draw and manage button for each position axis in the menu
 */
void	manage_pos(t_all *all, t_vector *pos, int y_start)
{
	minus_pos_axis(all, &pos->x, y_start);
	plus_pos_axis(all, &pos->x, y_start);

	minus_pos_axis(all, &pos->y, y_start + 20);
	plus_pos_axis(all, &pos->y, y_start + 20);

	minus_pos_axis(all, &pos->z, y_start + 40);
	plus_pos_axis(all, &pos->z, y_start + 40);
}

/*
 * Draw and manage minus button for one position axis
 */
static void	minus_pos_axis(t_all *all, float *channel, int y)
{
	but_set_pos(&all->menu.but_minus, WIDTH - 210, y);
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
		all->need_draw = true;
	}
	but_draw(all, &all->menu.but_minus);
}

/*
 * Draw and manage plus button for one position axis
 */
static void	plus_pos_axis(t_all *all, float *channel, int y)
{
	but_set_pos(&all->menu.but_plus, WIDTH - 190, y);
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
		all->need_draw = true;
	}
	but_draw(all, &all->menu.but_plus);
}
