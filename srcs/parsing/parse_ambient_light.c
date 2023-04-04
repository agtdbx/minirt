/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:32:43 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/04 14:12:52 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>

// t_result	parse_ambient_light(
// 				t_scene *ret_scene)
// {
// 	static bool	is_initialized = false;
// 	char		*tok;
//
// 	if (is_initialized)
// 		return (FAILURE);
// 	is_initialized = true;
// 	tok = ft_strtok(NULL, " \n");
// 	if (parse_brightness(tok, &ret_scene->ambient_light.brightness) == FAILURE)
// 		return (FAILURE);
// 	tok = ft_strtok(NULL, " \n");
// 	if (parse_color(tok, &ret_scene->ambient_light.color) == FAILURE)
// 		return (FAILURE);
// 	tok = ft_strtok(NULL, " \n");
// 	if (tok != NULL)
// 		return (FAILURE);
// 	compute_intensity(&ret_scene->ambient_light);
// 	return (SUCCESS);
// }

t_parsing_error	parse_ambient_light(
					t_directive_info const *directive,
					t_scene *ret_scene)
{
	float	brightness;

	parse_brightness(directive, directive->tokens->next, &brightness);
	(void) ret_scene;
	return (PARSING_SUCCESS);
}
