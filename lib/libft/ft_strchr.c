/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:44:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/01 19:52:30 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_strchr:
 *	  - returns a pointer toward the first occurence of byte c
 *	    in null terminated string str.
 *    - returns NULL if c is not found.
 */
char	*ft_strchr(
			char const *str,
			int c)
{
	char const	_c = c;

	while (*str != '\0' && *str != _c)
		str++;
	if (*str == _c)
		return ((char *)str);
	return (NULL);
}
