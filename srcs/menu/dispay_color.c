/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispay_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:57:01 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/04 14:02:54 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
 * Draw each color channel in differents lines in the menu
 */
void	display_color(t_all *all, t_color *color, int y_start)
{
	char	*tmp;
	char	*to_print;

	tmp = ft_itoa(color->r);
	to_print = ft_strjoin("color : r ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 400, y_start);
	free(tmp);
	free(to_print);

	tmp = ft_itoa(color->g);
	to_print = ft_strjoin("g ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 320, y_start + 20);
	free(tmp);
	free(to_print);

	tmp = ft_itoa(color->b);
	to_print = ft_strjoin("b ", tmp);
	mlx_put_string(all->mlx, to_print, WIDTH - 320, y_start + 40);
	free(tmp);
	free(to_print);
}
