/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:53:39 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/01 19:56:40 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>

size_t	ft_strcspn(
			char const *str,
			char const *reject)
{
	register size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		if (ft_strchr(reject, str[len]) != NULL)
			return (len);
		len++;
	}
	return (len);
}
