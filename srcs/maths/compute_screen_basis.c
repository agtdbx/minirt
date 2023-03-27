/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_screen_basis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:54:17 by tdubois           #+#    #+#             */
/*   Updated: 2023/03/27 17:54:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	compute_screen_basis(t_camera *ret_cam)
{
	float const	len = WIDTH_DIV_2 / tan(ret_cam->fov * PI_DIV_360);
	t_vector	tmp_basis[2];

	dup_vec(&ret_cam->orientation, &ret_cam->basis[2]);
	multiply_vec_number(&ret_cam->orientation, len);
	get_screen_basis(&ret_cam->basis[2], tmp_basis, 1);
	dup_vec(&ret_cam->basis[0], &tmp_basis[0]);
	dup_vec(&ret_cam->basis[1], &tmp_basis[1]);
	normalize_vec(&ret_cam->basis[0]);
	normalize_vec(&ret_cam->basis[1]);
}
