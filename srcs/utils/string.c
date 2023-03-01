/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:55:28 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/01 14:52:39 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_strtok_r(char *str, char const *sep, char **saveptr)
{
	char	*tok;

	if (str == NULL && *saveptr == NULL)
		return (NULL);
	if (str == NULL)
		tok = *saveptr;
	else
		tok = str;
	tok += ft_strspn(tok, sep);
	if (tok[0] == '\0')
	{
		*saveptr = NULL;
		return (NULL);
	}
	*saveptr = tok + ft_strcspn(tok, sep);
	*saveptr += ft_strspn(*saveptr, sep);
	tok[ft_strcspn(tok, sep)] = '\0';
	return (tok);
}

char	*ft_strtok(char *str, char const *sep)
{
	static char	*tok = NULL;

	return (ft_strtok_r(str, sep, &tok));
}
