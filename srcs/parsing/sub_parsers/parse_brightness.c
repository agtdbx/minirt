/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_brightness.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:19:05 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/05 14:42:36 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>
#include <unistd.h>

#include "libft.h"

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	parse_brightness(
					t_directive_info const *directive,
					t_itok const *tok,
					float *ret_brightness);

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	parse_brightness(
					t_directive_info const *directive,
					t_itok const *tok,
					float *ret_brightness)
{
	char	*endptr;

	if (!ft_isdigit(tok->token[0]))
	{
		put_directive_error(directive, "brightness: unexpected chars", tok);
		return (PARSING_ERROR);
	}
	*ret_brightness = ft_strtof(tok->token, &endptr);
	if (*ret_brightness < 0.0f || 1.0f < *ret_brightness)
	{
		put_directive_error(directive,
			"expected brightness in range (0.0, 1.0)", tok);
		return (PARSING_ERROR);
	}
	if (endptr[0] != '\0')
	{
		put_directive_error(directive, "brightness: unexpected chars", tok);
		return (PARSING_ERROR);
	}
	return (PARSING_SUCCESS);
}
