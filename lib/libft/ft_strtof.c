/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:19:25 by tdubois           #+#    #+#             */
/*   Updated: 2023/03/31 13:39:40 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <float.h>

// static float	get_fractional_part(char const *str, char **endptr);

float	ft_strtof(char const *str, char **endptr)
{
	double	ret;
	double	exponent;

	ret = 0.0f;
	while (ft_isdigit(str[0]))
	{
		ret = ret * 10.0f + ((double)(str[0] - '0'));
		str++;
	}
	*endptr = (char *)str;
	if (str[0] != '.')
		return (ret);
	if (!ft_isdigit(str[1]))
		return (ret);
	str++;
	exponent = 0.1f;
	while (ft_isdigit(str[0]))
	{
		ret += ((double)(str[0] - '0')) * exponent;
		str++;
		exponent /= 10.0f;
	}
	*endptr = (char *)str;
	return (ret);
}

// static float	get_fractional_part(char const *str, char **endptr)
// {
// 	float	ret;
// 	float	exponent;
//
// 	ret = 0.0f;
// 	exponent = 0.1f;
// 	while (ft_isdigit(str[0]))
// 	{
// 		ret += ((float)(str[0] - '0')) * exponent;
// 		str++;
// 		(*endptr)++;
// 		exponent /= 10.0f;
// 	}
// 	return (ret);
// }
