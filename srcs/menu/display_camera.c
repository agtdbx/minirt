/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:38:57 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/03 16:39:09 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	display_camera(t_all *all, t_camera *camera)
{
	(void)camera;
	mlx_put_string(all->mlx, "CAMERA", WIDTH - 240, 100);
}
