/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_itok_lst_size_is.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:57:35 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/05 14:44:48 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	assert_itok_lst_size_is(
					t_directive_info const *directive,
					t_itok const *toks,
					size_t expected_size);

static void		loc_not_enough_args_error(
					t_directive_info const *directive);

static void		loc_too_many_args_error(
					t_directive_info const *directive,
					size_t expected_size);

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	assert_itok_lst_size_is(
					t_directive_info const *directive,
					t_itok const *toks,
					size_t expected_size)
{
	size_t	i;

	i = 0;
	while (toks != NULL)
	{
		toks = toks->next;
		i++;
	}
	if (i == expected_size)
		return (PARSING_SUCCESS);
	if (i < expected_size)
		loc_not_enough_args_error(directive);
	if (expected_size < i)
		loc_too_many_args_error(directive, expected_size);
	return (PARSING_ERROR);
}

static void	loc_not_enough_args_error(
			t_directive_info const *directive)
{
	t_itok const	*toks;

	printf(
		"Error\n"
		"\n"
		"%s: line %lu: ", directive->filename, directive->lineno);
	toks = directive->tokens;
	while (toks != NULL)
	{
		printf("%s ", toks->token);
		toks = toks->next;
	}
	printf(RED"... "NC);
	printf(
		"\n"
		"│\n"
		"│  not enough arguments\n");
}

static void	loc_too_many_args_error(
			t_directive_info const *directive,
			size_t expected_size)
{
	t_itok const	*toks;
	size_t			i;

	printf(
		"Error\n"
		"\n"
		"%s: line %lu: ", directive->filename, directive->lineno);
	toks = directive->tokens;
	i = 0;
	while (toks != NULL)
	{
		if (i > expected_size)
			printf(RED"%s "NC, toks->token);
		else
			printf("%s ", toks->token);
		toks = toks->next;
		i++;
	}
	printf(
		"\n"
		"│\n"
		"│  too many arguments\n");
}
