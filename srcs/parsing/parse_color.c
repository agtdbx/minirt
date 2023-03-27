/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:17:29 by tdubois           #+#    #+#             */
/*   Updated: 2023/03/27 16:33:17 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include "libft.h"

static t_result	parse_channel(char const *nptr, int *ret_channel);

t_result	parse_color(char *rgb_str, t_color *ret_color)
{
	char	*saveptr;
	char	*nptr;

	nptr = ft_strtok_r(rgb_str, ",", &saveptr);
	if (parse_channel(nptr, &ret_color->r) == FAILURE)
		return (FAILURE);
	nptr = ft_strtok_r(NULL, ",", &saveptr);
	if (parse_channel(nptr, &ret_color->g) == FAILURE)
		return (FAILURE);
	if (ft_strchr(saveptr, ',') != NULL)
		return (FAILURE);
	nptr = ft_strtok_r(NULL, ",", &saveptr);
	if (parse_channel(nptr, &ret_color->b) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static t_result	parse_channel(char const *nptr, int *ret_channel)
{
	if (nptr == NULL)
		return (FAILURE);
	if (is_int(nptr) == false)
		return (FAILURE);
	*ret_channel = ft_atoi(nptr);
	if (*ret_channel < 0 || 255 < *ret_channel)
		return (FAILURE);
	return (SUCCESS);
}
