/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itok_hilight_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:37:05 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/04 15:25:18 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>

//TODO remove printf
void	itok_hilight_error(
			char const *filename,
			size_t line_no,
			t_itok const *toks,
			t_itok const *tok_to_hilight)
{
	printf("Error\n");
	printf("\n");
	printf("%s: line %lu, col %lu: ", filename, line_no, toks->index);
	while (toks != NULL)
	{
		if (toks == tok_to_hilight)
			printf(RED);
		printf("%s", toks->token);
		if (toks->next != NULL)
			printf(" ");
		if (toks == tok_to_hilight)
			printf(NC);
		toks = toks->next;
	}
	printf("\n");
}
