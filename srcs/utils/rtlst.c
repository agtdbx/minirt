/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtlst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:19:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/31 16:14:07 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_rtlst	*rtlst_new(t_rtlst_t type, t_rtlst_v value, int id)
{
	t_rtlst	*new;

	new = malloc(sizeof(t_rtlst));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	new->id = id;
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

t_rtlst	*get_obj_by_index(t_rtlst *rtlst, int id)
{
	t_rtlst	*tmp;

	if (id < 0)
		return (NULL);
	tmp = rtlst;
	while (tmp)
	{
		if (tmp->id == id)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
