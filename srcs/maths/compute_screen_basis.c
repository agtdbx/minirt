/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_screen_basis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:54:17 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/17 16:25:18 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	compute_screen_basis(t_camera *ret_cam)
{
	t_vec3	tmp_basis[2];

	ret_cam->len = WIDTH_DIV_2 / tan(ret_cam->fov * PI_DIV_360);
	vec3_dup(&ret_cam->orientation, &ret_cam->basis[2]);
	vec3_multiply_number(&ret_cam->orientation, ret_cam->len);
	get_screen_basis(&ret_cam->basis[2], tmp_basis, 1);
	vec3_dup(&ret_cam->basis[0], &tmp_basis[0]);
	vec3_dup(&ret_cam->basis[1], &tmp_basis[1]);
	vec3_normalize(&ret_cam->basis[0]);
	vec3_normalize(&ret_cam->basis[1]);
}
