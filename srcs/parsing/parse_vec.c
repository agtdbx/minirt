/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:48 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/27 16:59:30 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include "libft.h"

static t_result	parse_coordinate(char const *nptr, float *ret_coordinate);

t_result	parse_vec(char *xyz_str, t_vector *ret_vec)
{
	char	*saveptr;
	char	*nptr;

	nptr = ft_strtok_r(xyz_str, ",", &saveptr);
	if (parse_coordinate(nptr, &ret_vec->x) == FAILURE)
		return (FAILURE);
	nptr = ft_strtok_r(NULL, ",", &saveptr);
	if (parse_coordinate(nptr, &ret_vec->y) == FAILURE)
		return (FAILURE);
	if (ft_strchr(saveptr, ',') != NULL)
		return (FAILURE);
	nptr = ft_strtok_r(NULL, ",", &saveptr);
	if (parse_coordinate(nptr, &ret_vec->z) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static t_result	parse_coordinate(char const *nptr, float *ret_coordinate)
{
	if (nptr == NULL)
		return (FAILURE);
	if (is_float(nptr) == false)
		return (FAILURE);
	*ret_coordinate = ft_atof(nptr);
	return (SUCCESS);
}
