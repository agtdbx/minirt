/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:52:02 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/01 14:52:33 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(char const *str, char const *accept)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && ft_strchr(accept, str[i]) != NULL)
	{
		i++;
	}
	return (i);
}
