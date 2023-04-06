/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:43:15 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/06 12:06:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	cur_set_pos(t_cursor *cur, int const x, int const y)
{
	cur->x = x;
	cur->y = y;
}

void	cur_draw(t_all *all, t_cursor const *cur)
{
	int	x;
	int	y;

	y = 0;
	while (y < cur->height)
	{
		x = 0;
		while (x < cur->width)
		{
			if (x == 0 || x == cur->width - 1 || y == 0 || y == cur->height - 1)
				mlx_put_pixel(all->img, cur->x + x, cur->y + y, 0xFFFFFFFF);
			else if (cur->select - 1 <= x && x <= cur->select + 1)
				mlx_put_pixel(all->img, cur->x + x, cur->y + y, 0x999999FF);
			x++;
		}
		y++;
	}
}

void	cur_tick(t_all *all, t_cursor *cur)
{
	if (all->mouse.pressed
		&& cur->x <= all->mouse.x && all->mouse.x <= cur->x + cur->width
		&& cur->y <= all->mouse.y && all->mouse.y <= cur->y + cur->height)
		cur->select = all->mouse.x - cur->x;
}
