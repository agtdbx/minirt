/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_screen_basis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:54:17 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/14 12:01:39 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	compute_screen_basis(t_camera *ret_cam)
{
	t_vector	tmp_basis[2];

	ret_cam->len = WIDTH_DIV_2 / tan(ret_cam->fov * PI_DIV_360);
	dup_vec(&ret_cam->orientation, &ret_cam->basis[2]);
	multiply_vec_number(&ret_cam->orientation, ret_cam->len);
	get_screen_basis(&ret_cam->basis[2], tmp_basis, 1);
	dup_vec(&ret_cam->basis[0], &tmp_basis[0]);
	dup_vec(&ret_cam->basis[1], &tmp_basis[1]);
	normalize_vec(&ret_cam->basis[0]);
	normalize_vec(&ret_cam->basis[1]);
}
