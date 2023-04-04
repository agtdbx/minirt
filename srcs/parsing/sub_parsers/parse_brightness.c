/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_brightness.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:19:05 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/04 15:35:03 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>

#include "libft.h"

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	parse_brightness(
					t_directive_info const *directive,
					t_itok const *tok,
					float *ret_brightness);

static void		loc_put_unexpected_leading_char_err(
					t_directive_info const *directive,
					t_itok const *tok);

static void		loc_put_unexpected_char_err(
					t_directive_info const *directive,
					t_itok const *tok,
					size_t char_idx);

static void		loc_put_range_err(
					t_directive_info const *directive,
					t_itok const *tok,
					char const *endptr);

////////////////////////////////////////////////////////////////////////////////

t_parsing_error	parse_brightness(
					t_directive_info const *directive,
					t_itok const *tok,
					float *ret_brightness)
{
	char	*endptr;

	if (!ft_isdigit(tok->token[0]))
	{
		loc_put_unexpected_leading_char_err(directive, tok);
		return (PARSING_ERROR);
	}
	*ret_brightness = ft_strtof(tok->token, &endptr);
	if (*ret_brightness < 0.0f || 1.0f < *ret_brightness)
	{
		loc_put_range_err(directive, tok, endptr);
		return (PARSING_ERROR);
	}
	if (endptr[0] != '\0')
	{
		loc_put_unexpected_char_err(directive, tok, endptr - tok->token);
		return (PARSING_ERROR);
	}
	return (PARSING_SUCCESS);
}

static void	loc_put_unexpected_leading_char_err(
				t_directive_info const *directive,
				t_itok const *tok)
{
	size_t const	len = ft_strcspn(tok->token, "0123456789");

	itok_hilight_error(
		directive->filename, directive->lineno, directive->tokens, tok);
	ft_putstr_fd("│\n", 2);
	ft_putstr_fd("│  Error while parsing brightness:\n", 2);
	ft_putstr_fd("│\n", 2);
	ft_putstr_fd("│  ", 2);
	ft_putstr_fd(RED, 2);
	write(2, tok->token, len);
	ft_putstr_fd(NC, 2);
	ft_putstr_fd(tok->token + len, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("│  ┬", 2);
	ft_putstr_rpt_fd("─", len - 1, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("│  ", 2);
	ft_putstr_fd("╰╴unexpected chars `", 2);
	write(2, tok->token, len);
	ft_putstr_fd("'\n", 2);
}

static void	loc_put_unexpected_char_err(
				t_directive_info const *directive,
				t_itok const *tok,
				size_t char_idx)
{
	itok_hilight_error(
		directive->filename, directive->lineno, directive->tokens, tok);
	ft_putstr_fd("│\n", 2);
	ft_putstr_fd("│  Error while parsing brightness:\n", 2);
	ft_putstr_fd("│\n", 2);
	ft_putstr_fd("│  ", 2);
	write(2, tok->token, char_idx);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(tok->token + char_idx, 2);
	ft_putstr_fd(NC, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("│  ", 2);
	ft_putstr_rpt_fd(" ", char_idx, 2);
	ft_putstr_fd("┬", 2);
	ft_putstr_rpt_fd("─", ft_strlen(tok->token) - char_idx - 1, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("│  ", 2);
	ft_putstr_rpt_fd(" ", char_idx, 2);
	ft_putstr_fd("╰╴unexpected chars `", 2);
	ft_putstr_fd(tok->token + char_idx, 2);
	ft_putstr_fd("'\n", 2);
}

static void	loc_put_range_err(
				t_directive_info const *directive,
				t_itok const *tok,
				char const *endptr)
{
	itok_hilight_error(
		directive->filename, directive->lineno, directive->tokens, tok);
	ft_putstr_fd("│\n", 2);
	ft_putstr_fd("│  Error while parsing brightness:\n", 2);
	ft_putstr_fd("│\n", 2);
	ft_putstr_fd("│  ", 2);
	ft_putstr_fd(RED, 2);
	write(2, tok->token, endptr - tok->token);
	ft_putstr_fd(NC, 2);
	ft_putstr_fd(endptr, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("│  ┬", 2);
	ft_putstr_rpt_fd("─", endptr - tok->token - 1, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("│  ╰╴brightness out of bound: 0.0 ≰ `", 2);
	write(2, tok->token, endptr - tok->token);
	ft_putstr_fd("' ≰ 1.0\n", 2);
}
