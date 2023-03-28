/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:23:40 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/28 12:23:58 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_result	parse_direction(char *xyz_str, t_vector *ret_vec)
{
	if (parse_vec(xyz_str, ret_vec) == FAILURE)
		return (FAILURE);
	if (is_xyz_in_range(ret_vec, -1.0f, 1.0f) == FAILURE)
		return (FAILURE);
	if (ret_vec->x == 0.0f && ret_vec->y == 0.0f && ret_vec->z == 0.0f)
		return (FAILURE);
	normalize_vec(ret_vec);
	return (SUCCESS);
}
