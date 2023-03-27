/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_xyz_in_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:56:20 by tdubois           #+#    #+#             */
/*   Updated: 2023/03/27 18:52:17 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdbool.h>

bool	is_xyz_in_range(t_vector const *vec, float min, float max)
{
	if (vec->x < min || max < vec->x)
		return (false);
	if (vec->y < min || max < vec->y)
		return (false);
	if (vec->z < min || max < vec->z)
		return (false);
	return (true);
}
