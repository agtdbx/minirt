/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:48:57 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/01 14:52:42 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(char const *str, char const *reject)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && ft_strchr(reject, str[i]) == NULL)
	{
		i++;
	}
	return (i);
}
