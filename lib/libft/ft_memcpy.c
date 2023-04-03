/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:13:27 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/03 00:18:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>

void	*ft_memcpy(
			void *dst,
			void const *src,
			size_t src_size)
{
	char		*c_dst;
	char const	*c_src;
	size_t		i;

	c_dst = dst;
	c_src = src;
	i = 0;
	while (i < src_size)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	return (dst);
}
