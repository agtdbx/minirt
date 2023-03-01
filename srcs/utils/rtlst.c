/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtlst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:19:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/01 18:50:33 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_rtlst	*rtlst_new(t_rtlst_t type, t_rtlst_v value)
{
	t_rtlst	*new;

	new = malloc(sizeof(t_rtlst));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	rtlst_add_back(t_rtlst **rtlst, t_rtlst *new)
{
	t_rtlst	*tmp;

	if (rtlst == NULL)
		return ;
	if (*rtlst == NULL)
	{
		*rtlst = new;
		return ;
	}
	tmp = *rtlst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	rtlst_free(t_rtlst **rtlst)
{
	t_rtlst	*next;

	if (rtlst == NULL)
		return ;
	while (*rtlst)
	{
		next = (*rtlst)->next;
		free(*rtlst);
		*rtlst = next;
	}
	*rtlst = NULL;
}
