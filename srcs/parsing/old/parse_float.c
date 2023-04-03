/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:40:43 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/28 12:42:18 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_result	parse_float(char const *nptr, float *ret_float)
{
	if (is_float(nptr) == false)
		return (FAILURE);
	*ret_float = ft_atof(nptr);
	return (SUCCESS);
}
