/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/04 12:43:24 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_plane(t_all *all, t_plane *plane)
{
	(void)plane;

	// Si on a pas d'update, on ne draw pas le text
	if (all->text_draw == false)
		return ;

	mlx_put_string(all->mlx, "PLANE", WIDTH - 230, 100);
}
