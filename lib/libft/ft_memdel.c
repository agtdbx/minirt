/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:07:37 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/03 09:00:39 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <stddef.h>

void	ft_memdel(void *bufptr)
{
	char	**cbufptr;

	cbufptr = bufptr;
	if (*cbufptr != NULL)
	{
		free(*cbufptr);
	}
	*cbufptr = NULL;
}
