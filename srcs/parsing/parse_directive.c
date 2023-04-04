/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:25:38 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/04 15:36:52 by tdubois          ###   ########.fr       */
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
	size_t				i;
	t_parsing_error		err;
	t_directive_info	info;

	if (ft_strspn(line, " \n") == ft_strlen(line))
		return (PARSING_SUCCESS);
	info.tokens = itok_split(line, " \n");
	if (info.tokens == NULL)
		return (PARSING_ERROR);
	i = 0;
	while (g_directives[i].identifier != NULL
		&& strcmp(g_directives[i].identifier, info.tokens->token) != 0)
		i++;
	err = PARSING_ERROR;
	if (g_directives[i].identifier == NULL)
		loc_put_err(line_no, filename, info.tokens);
	else
	{
		info.lineno = i;
		info.filename = filename;
		err = g_directives[i].parser(&info, ret_scene);
	}
	itok_del((void *)&info.tokens);
	return (err);
}

static void	loc_put_err(
				size_t line_no,
				char const *filename,
				t_itok const *toks)
{
	itok_hilight_error(filename, line_no, toks, toks);
	printf("│\n");
	printf("│  %s\n", toks->token);
	printf("│  ┬");
	fflush(stdout);
	ft_putstr_rpt_fd("─", ft_strlen(toks->token) - 1, 1);
	printf("\n");
	printf("│  ╰╴unknown identifier `%s'\n", toks->token);
}
