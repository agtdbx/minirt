/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:11:18 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/01 19:31:38 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>
#include <stdlib.h>

char	*ft_strdup(char const *str)
{
	char			*buf;
	const size_t	buf_size = ft_strlen(str) + 1;

	buf = malloc(buf_size);
	if (buf == NULL)
		return (NULL);
	ft_strlcpy(buf, str, buf_size);
	return (buf);
}
