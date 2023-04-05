/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:25:38 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/05 14:05:56 by tdubois          ###   ########.fr       */
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
	info = (t_directive_info){line_no, filename, itok_split(line, " \n")};
	if (info.tokens == NULL)
		return (PARSING_ERROR);
	i = 0;
	while (g_directives[i].identifier != NULL
		&& strcmp(g_directives[i].identifier, info.tokens->token) != 0)
		i++;
	if (g_directives[i].identifier == NULL)
	{
		err = PARSING_ERROR;
		put_directive_error(&info, "unknown identifier", 0);
	}
	else
		err = g_directives[i].parser(&info, ret_scene);
	itok_del((void *)&info.tokens);
	return (err);
}
