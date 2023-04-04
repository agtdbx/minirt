/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:35:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/04 12:38:48 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_light(t_all *all, t_light *light)
{
	(void)light;

	// Si on a pas d'update, on ne draw pas le text
	if (all->text_draw == false)
		return ;

	mlx_put_string(all->mlx, "LIGHT", WIDTH - 230, 100);
}
