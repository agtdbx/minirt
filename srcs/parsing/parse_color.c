/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:02:48 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/05 14:45:34 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <errno.h>

////////////////////////////////////////////////////////////////////////////////

t_parsing_error			parse_color(
							t_directive_info const *directive,
							t_itok const *tok,
							t_color *ret_color);

static t_parsing_error	loc_parse_channel(
							t_directive_info const *directive,
							t_itok const *color_tok,
							t_itok const *channel_tok,
							int *ret_channel);

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	parse_color(
					t_directive_info const *directive,
					t_itok const *tok,
					t_color *ret_color)
{
	t_itok			*channels;
	t_parsing_error	ret;

	ret = PARSING_SUCCESS;
	channels = itok_split(tok->token, ",");
	if (assert_itok_lst_size_is(directive, channels, 3) == PARSING_ERROR)
		ret = PARSING_ERROR;
	if (ret != PARSING_ERROR)
		ret = loc_parse_channel(directive, tok, channels, &ret_color->r);
	if (ret != PARSING_ERROR)
		ret = loc_parse_channel(directive, tok, channels->next, &ret_color->g);
	if (ret != PARSING_ERROR)
	{
		ret = loc_parse_channel(
				directive, tok, channels->next->next, &ret_color->b);
	}
	itok_del(&channels);
	return (ret);
}

static t_parsing_error	loc_parse_channel(
							t_directive_info const *directive,
							t_itok const *color_tok,
							t_itok const *channel_tok,
							int *ret_channel)
{
	char	*endptr;

	if (!ft_isdigit(channel_tok->token[0]))
	{
		put_directive_error(directive, "color: unexpected chars", color_tok);
		return (PARSING_ERROR);
	}
	errno = 0;
	*ret_channel = ft_strtoi(channel_tok->token, &endptr);
	if (errno == ERANGE || *ret_channel < 0 || 255 < *ret_channel)
	{
		put_directive_error(directive,
			"expected color in range [0, 255]", color_tok);
		return (PARSING_ERROR);
	}
	if (endptr[0] != '\0')
	{
		put_directive_error(directive, "color: unexpected chars", color_tok);
		return (PARSING_ERROR);
	}
	return (PARSING_SUCCESS);
}
