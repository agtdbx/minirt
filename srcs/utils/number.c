/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:49:20 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/28 16:24:31 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	nb_point_int_str(char const *str);

bool	is_int(char const *str)
{
	int		start;
	int		len;
	long	test;

	if (!str)
		return (false);
	start = 0;
	if (str[0] == '-')
		start++;
	if (start == 1 && str[start] == '\0')
		return (false);
	while (str[start] == '0')
		start++;
	len = ft_strlen(str);
	if (len == 0 || len - start > 11)
		return (false);
	while (str[start] >= '0' && str[start] <= '9')
		start++;
	if (start != len)
		return (false);
	test = ft_atol(str);
	if (test > 2147483647 || test < -2147483648)
		return (false);
	return (true);
}

bool	is_float(char const *str)
{
	char	*part;
	char	*saveptr;
	char	*dup_str;

	if (!str)
		return (false);
	if (nb_point_int_str(str) > 1)
		return (false);
	dup_str = ft_strdup(str);
	part = ft_strtok_r(dup_str, ".", &saveptr);
	if (is_int(part) == false)
	{
		free(dup_str);
		return (false);
	}
	part = ft_strtok_r(NULL, ".", &saveptr);
	if (part != NULL && is_int(part) == false)
	{
		free(dup_str);
		return (false);
	}
	free(dup_str);
	return (true);
}

static int	nb_point_int_str(char const *str)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (str[i] == '.')
			cpt++;
		i++;
	}
	return (cpt);
}
