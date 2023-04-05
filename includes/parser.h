/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:27:35 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/04 14:11:16 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "main.h"

////////////////////////////////////////////////////////////////////////////////
/// TYPES

# define RED "\033[91m"
# define NC  "\033[0m"

typedef struct s_itok
{
	size_t			index;
	char const		*token;
	struct s_itok	*next;
}	t_itok;

t_itok			*itok_split(
					char const *str,
					char const *sep);

void			itok_del(
					t_itok **toks);

void			itok_hilight_error(
					char const *filename,
					size_t line_no,
					t_itok const *toks,
					t_itok const *tok_to_hilight);

typedef enum e_parsing_error
{
	PARSING_SUCCESS,
	PARSING_ERROR
}	t_parsing_error;

typedef struct s_directive_info
{
	size_t 			lineno;
	char const		*filename;
	t_itok const	*tokens;
}	t_directive_info;

typedef t_parsing_error	(*t_directive_parser)(
							t_directive_info const *directive,
							t_scene *ret_scene);

typedef struct s_directive
{
	char const					*identifier;
	t_directive_parser const	parser;
}	t_directive;


////////////////////////////////////////////////////////////////////////////////
/// METHODS

t_parsing_error	parse_file(
					char const *filename,
					t_scene *ret_scene);

t_parsing_error	parse_directive(
					size_t lineno,
					char const *filename,
					char const *line,
					t_scene *ret_scene);

//////////////
// DIRECTIVES 

t_parsing_error	parse_ambient_light(
					t_directive_info const *directive,
					t_scene *ret_scene);


///////////////
// SUB PARSERS

t_parsing_error	parse_brightness(
					t_directive_info const *directive,
					t_itok const *tok,
					float *ret_brightness);

#endif //PARSER_H