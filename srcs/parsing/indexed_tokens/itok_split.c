/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itok_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:31:12 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/04 13:46:34 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stddef.h>
#include <stdlib.h>

#include "libft.h"

////////////////////////////////////////////////////////////////////////////////

t_itok			*itok_split(
					char const *str,
					char const *sep);

static t_itok	*loc_itok_from_substr(
					char const *str,
					size_t idx,
					size_t len);

static void		loc_itok_add_back(
					t_itok **toks,
					t_itok const *new_tok);

////////////////////////////////////////////////////////////////////////////////

t_itok	*itok_split(
			char const *str,
			char const *sep)
{
	t_itok	*toks;
	t_itok	*new_tok;
	size_t	idx;
	size_t	len;

	toks = NULL;
	idx = 0;
	while (str[idx] != '\0')
	{
		idx += ft_strspn(str + idx, sep);
		if (str[idx] == '\0')
			return (toks);
		len = ft_strcspn(str + idx, sep);
		new_tok = loc_itok_from_substr(str, idx, len);
		if (new_tok == NULL)
		{
			itok_del(&toks);
			return (NULL);
		}
		loc_itok_add_back(&toks, new_tok);
		idx += len;
	}
	return (toks);
}

static t_itok	*loc_itok_from_substr(
					char const *str,
					size_t idx,
					size_t len)
{
	t_itok	*tok;

	tok = malloc(sizeof(t_itok));
	if (tok == NULL)
		return (NULL);
	tok->next = NULL;
	tok->index = idx;
	tok->token = ft_substr(str, idx, len);
	if (tok->token == NULL)
	{
		ft_memdel(&tok);
		return (NULL);
	}
	return (tok);
}

static void	loc_itok_add_back(
				t_itok **toks,
				t_itok const *new_tok)
{
	while (*toks != NULL)
		toks = &(*toks)->next;
	*toks = (t_itok *)new_tok;
}