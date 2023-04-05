/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_directive_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:37:05 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/05 14:11:30 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>

void	put_directive_error(
			t_directive_info const *directive,
			char const *msg,
			t_itok const *tok_to_hilight)
{
	t_itok const	*toks;

	printf(
		"Error\n"
		"\n"
		"%s: line %lu: ", directive->filename, directive->lineno);
	toks = directive->tokens;
	while (toks != NULL)
	{
		if (toks == tok_to_hilight)
			printf(RED"%s "NC, toks->token);
		else
			printf("%s ", toks->token);
		toks = toks->next;
	}
	printf(
		"\n"
		"│\n"
		"│  %s\n", msg);
}
