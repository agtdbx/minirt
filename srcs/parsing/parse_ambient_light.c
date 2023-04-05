/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:32:43 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/05 14:04:33 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	parse_ambient_light(
					t_directive_info const *directive,
					t_scene *ret_scene);

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	parse_ambient_light(
					t_directive_info const *directive,
					t_scene *ret_scene)
{
	t_itok	*toks;

	toks = directive->tokens->next;
	if (assert_itok_lst_size_is(directive, toks, 2) == PARSING_ERROR)
		return (PARSING_ERROR);
	if (parse_brightness(directive, toks,
			&ret_scene->ambient_light.brightness) == PARSING_ERROR)
		return (PARSING_ERROR);
	toks = toks->next;
	if (parse_color(directive, toks,
			&ret_scene->ambient_light.color) == PARSING_ERROR)
		return (PARSING_ERROR);
	return (PARSING_SUCCESS);
}
