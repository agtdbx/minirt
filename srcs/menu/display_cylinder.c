/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:34:26 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/05 16:58:25 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_cylinder(t_all *all, t_cylinder *cylinder)
{
	(void)cylinder;

	// Si on a pas d'update, on ne draw pas le text
	if (all->draw_state != DRAW_TEXT)
		return ;

	mlx_put_string(all->mlx, "CYLINDER", WIDTH - 250, 100);
}
