/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendswith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:09:01 by tdubois           #+#    #+#             */
/*   Updated: 2023/03/27 12:11:42 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdbool.h>
#include <stddef.h>

bool	ft_strendswith(char const *str, char const *suffix)
{
	int const	len_str = ft_strlen(str);
	int const	len_suffix = ft_strlen(suffix);

	if (len_str < len_suffix)
		return (false);
	return (ft_strcmp(str + len_str - len_suffix, suffix) == 0);
}
