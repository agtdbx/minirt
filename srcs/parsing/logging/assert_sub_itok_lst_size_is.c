/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_sub_itok_lst_size_is.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:57:35 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/05 17:48:38 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	assert_sub_itok_lst_size_is(
					t_directive_info const *directive,
					t_itok const *container,
					t_itok const *toks,
					size_t expected_size);

static void		loc_not_enough_args_error(
					t_directive_info const *directive,
					t_itok const *container);

static void		loc_too_many_args_error(
					t_directive_info const *directive,
					t_itok const *container,
					t_itok const *toks,
					size_t expected_size);

static void		loc_print_subtoks(
					t_itok const *sub_toks,
					size_t expected_size);

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	assert_sub_itok_lst_size_is(
					t_directive_info const *directive,
					t_itok const *container,
					t_itok const *sub_toks,
					size_t expected_size)
{
	size_t			i;
	t_itok const	*toks;

	toks = sub_toks;
	i = 0;
	while (toks != NULL)
	{
		toks = toks->next;
		i++;
	}
	if (i == expected_size)
		return (PARSING_SUCCESS);
	if (i < expected_size)
		loc_not_enough_args_error(directive, container);
	if (expected_size < i)
		loc_too_many_args_error(directive, container, sub_toks, expected_size);
	return (PARSING_ERROR);
}

static void	loc_not_enough_args_error(
			t_directive_info const *directive,
			t_itok const *container)
{
	t_itok const	*toks;

	printf(
		"Error\n"
		"\n"
		"%s: line %lu: ", directive->filename, directive->lineno);
	toks = directive->tokens;
	while (toks != NULL)
	{
		if (toks == container)
			printf("%s"RED"... "NC, toks->token);
		else
			printf("%s ", toks->token);
		printf(" ");
		toks = toks->next;
	}
	printf(
		"\n"
		"│\n"
		"│  not enough arguments\n");
}

static void	loc_too_many_args_error(
			t_directive_info const *directive,
			t_itok const *container,
			t_itok const *sub_toks,
			size_t expected_size)
{
	t_itok const	*toks;

	printf(
		"Error\n"
		"\n"
		"%s: line %lu: ", directive->filename, directive->lineno);
	toks = directive->tokens;
	while (toks != NULL)
	{
		if (toks == container)
			loc_print_subtoks(sub_toks, expected_size);
		else
			printf("%s ", toks->token);
		toks = toks->next;
	}
	printf(
		"\n"
		"│\n"
		"│  too many arguments\n");
}

static void	loc_print_subtoks(
				t_itok const *sub_toks,
				size_t expected_size)
{
	size_t	i;

	i = 1;
	while (sub_toks != NULL)
	{
		printf("%s", sub_toks->token);
		i++;
		if (i > expected_size)
			printf(RED);
		if (sub_toks->next != NULL)
			printf(",");
		sub_toks = sub_toks->next;
	}
	printf(NC);
}
