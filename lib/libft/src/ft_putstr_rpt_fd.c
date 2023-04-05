/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_rpt_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:23:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/03 16:45:09 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>

void	ft_putstr_rpt_fd(
			char const *str,
			size_t niter,
			int fd)
{
	size_t	i;

	i = 0;
	while (i < niter)
	{
		ft_putstr_fd(str, fd);
		i++;
	}
}
