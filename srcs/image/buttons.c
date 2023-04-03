/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:34:34 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/03 16:34:06 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	but_set_pos(t_button *but, int const x, int const y)
{
	but->x = x;
	but->y = y;
}

void	but_draw(t_all *all, t_button const *but)
{
	int	size_text;
	int	x;
	int	y;

	y = 0;
	while (y < but->height)
	{
		x = 0;
		while (x < but->width)
		{
			if (x == 0 || x == but->width - 1 || y == 0 || y == but->height - 1)
				mlx_put_pixel(all->img, but->x + x, but->y + y, 0xFFFFFFFF);
			else
				mlx_put_pixel(all->img, but->x + x, but->y + y, but->color);
			x++;
		}
		y++;
	}

	size_text = ft_strlen(but->text) * 10;
	x = but->x + ((but->width - size_text) / 2);
	y = but->y + ((but->height - 20) / 2);

	mlx_put_string(all->mlx, but->text, x, y);
}

bool	but_over(t_all *all, t_button *but)
{
	return (but->x <= all->mouse.x && all->mouse.x <= but->x + but->width
			&& but->y <= all->mouse.y && all->mouse.y <= but->y + but->height);
}

bool	but_click(t_all *all, t_button *but)
{
	return (all->mouse.pressed && but_over(all, but));
}
