/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itok_hilight_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:37:05 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/03 17:34:43 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>

#define RED "\033[91m"
#define NC  "\033[0m"

void	itok_hilight_error(
			t_itok const *toks,
			size_t index)
{
	size_t	i;

	i = 0;
	while (toks != NULL)
	{
		if (i == index)
			printf(RED);
		printf("%s", toks->token);
		if (toks->next != NULL)
			printf(" ");
		if (i == index)
			printf(NC);
		toks = toks->next;
		i++;
	}
	printf("\n");
}
