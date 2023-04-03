/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:32:43 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/03 17:00:39 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>

t_parsing_error	parse_ambient_light(
					size_t lineno,
					char const *filename,
					t_itok const *toks,
					t_scene *ret_scene)
{
	(void) lineno;
	(void) filename;
	(void) toks;
	(void) ret_scene;
	return (PARSING_SUCCESS);
}
