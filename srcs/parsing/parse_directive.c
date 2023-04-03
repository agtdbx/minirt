/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:25:38 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/03 17:38:14 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#include "libft.h"
#include "main.h"

// "C",
// "L",
// "sp",
// "pl",
// "cy",

static const t_directive	g_directives[] = {
{"A", parse_ambient_light},
{NULL, NULL}
};

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	parse_directive(
					size_t line_no,
					char const *filename,
					char const *line,
					t_scene *ret_scene);

static void		loc_put_err(
					size_t line_no,
					char const *filename,
					t_itok const *toks);

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	parse_directive(
					size_t line_no,
					char const *filename,
					char const *line,
					t_scene *ret_scene)
{
	size_t			i;
	t_parsing_error	err;
	t_itok			*toks;

	if (ft_strspn(line, " \n") == ft_strlen(line))
		return (PARSING_SUCCESS);
	toks = itok_split(line, " \n");
	if (toks == NULL)
		return (PARSING_ERROR);
	i = 0;
	while (g_directives[i].identifier != NULL
		&& strcmp(g_directives[i].identifier, toks->token) != 0)
		i++;
	if (g_directives[i].identifier == NULL)
	{
		loc_put_err(line_no, filename, toks);
		err = PARSING_ERROR;
	}
	else
		err = g_directives[i].parser(line_no, filename, toks, ret_scene);
	itok_del(&toks);
	return (err);
}

static void	loc_put_err(
				size_t line_no,
				char const *filename,
				t_itok const *toks)
{
	printf("Error\n");
	printf("\n");
	printf("%s: line %lu, col %lu:\n", filename, line_no, toks->index);
	printf("│\n");
	printf("│  ");
	itok_hilight_error(toks, 0);
	printf("│  ┬");
	fflush(stdout);
	ft_putstr_rpt_fd("─", ft_strlen(toks->token) - 1, 0);
	printf("\n");
	printf("│  ╰╴unknown identifier `%s'\n", toks->token);
}
