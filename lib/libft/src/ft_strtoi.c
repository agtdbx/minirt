/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:59:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/05 11:01:31 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <limits.h>
#include <errno.h>

int	ft_strtoi(
		char const *nptr,
		char **endptr)
{
	long	n;
	long	digit;
	bool	is_neg;

	nptr += ft_strspn(nptr, " \f\n\r\t\v");
	is_neg = (*nptr == '-');
	nptr += (ft_strspn(nptr, "+-") > 0);
	n = 0;
	while (ft_isdigit(*nptr))
	{
		digit = *nptr - '0';
		if (n < (LONG_MIN + digit) / 10 || (LONG_MAX - digit) / 10 < n)
		{
			errno = ERANGE;
			if (is_neg)
				return ((int)LONG_MIN);
			return ((int)LONG_MAX);
		}
		n = n * 10 + (1 - 2 * is_neg) * digit;
		nptr++;
	}
	if (endptr != NULL)
		*endptr = (char *) nptr;
	return (n);
}
