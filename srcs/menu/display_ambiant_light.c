/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ambiant_light.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:35:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/05 11:48:57 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	minus_intensity(t_all *all, t_light *ambiant_light);
static void	plus_intensity(t_all *all, t_light *ambiant_light);
static void	cursor_intensity(t_all *all, t_light *ambiant_light);

/*
 * Draw and manage the ambiant light
 */
void	display_ambiant_light(t_all *all, t_light *ambiant_light)
{
	char	*tmp;
	char	*to_print;

	minus_intensity(all, ambiant_light);
	plus_intensity(all, ambiant_light);
	cursor_intensity(all, ambiant_light);
	manage_color(all, &ambiant_light->color, 180);
	if (all->text_draw == false)
		return ;
	mlx_put_string(all->mlx, "AMBIANT LIGHT", WIDTH - 270, 100);
	tmp = ft_ftoa(ambiant_light->brightness);
	to_print = ft_strjoin("intensity : ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 400, 140);
	free(tmp);
	free(to_print);
	display_color(all, &ambiant_light->color, 180);
}

static void	minus_intensity(t_all *all, t_light *ambiant_light)
{
	but_set_pos(&all->menu.but_minus, WIDTH - 160, 140);
	if (ambiant_light->brightness == 0.0f)
		all->menu.but_minus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_minus))
		all->menu.but_minus.color = 0x999999FF;
	else
		all->menu.but_minus.color = 0x666666FF;
	if (ambiant_light->brightness > 0.0f && but_click(all, &all->menu.but_minus))
	{
		ambiant_light->brightness -= 0.1f;
		if (ambiant_light->brightness < 0.0f)
			ambiant_light->brightness = 0.0f;
		all->menu.cur_float.select = ambiant_light->brightness * 40.0f;
		all->need_draw = true;
	}
	but_draw(all, &all->menu.but_minus);
}

static void	plus_intensity(t_all *all, t_light *ambiant_light)
{
	but_set_pos(&all->menu.but_plus, WIDTH - 140, 140);
	if (ambiant_light->brightness == 1.0f)
		all->menu.but_plus.color = 0x333333FF;
	else if (but_over(all, &all->menu.but_plus))
		all->menu.but_plus.color = 0x999999FF;
	else
		all->menu.but_plus.color = 0x666666FF;
	if (ambiant_light->brightness < 1.0f && but_click(all, &all->menu.but_plus))
	{
		ambiant_light->brightness += 0.1f;
		if (ambiant_light->brightness > 1.0f)
			ambiant_light->brightness = 1.0f;
		all->menu.cur_float.select = ambiant_light->brightness * 40.0f;
		all->need_draw = true;
	}
	but_draw(all, &all->menu.but_plus);
}

static void	cursor_intensity(t_all *all, t_light *ambiant_light)
{
	cur_set_pos(&all->menu.cur_float, WIDTH - 200, 140);
	cur_tick(all, &all->menu.cur_float);
	if (ambiant_light->brightness * 40.0f != all->menu.cur_float.select)
	{
		ambiant_light->brightness = (float)all->menu.cur_float.select / 40.0f;
		all->need_draw = true;
	}
	cur_draw(all, &all->menu.cur_float);
}
