/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imglst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:19:27 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/07 16:54:41 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_imglst	*imglst_new(mlx_image_t *img)
{
	t_imglst	*new;

	new = malloc(sizeof(t_imglst));
	if (!new)
		return (NULL);
	new->img = img;
	new->next = NULL;
	return (new);
}

void	imglst_add_back(t_imglst **imglst, t_imglst *new)
{
	t_imglst	*tmp;

	if (imglst == NULL)
		return ;
	if (*imglst == NULL)
	{
		*imglst = new;
		return ;
	}
	tmp = *imglst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	imglst_clear(t_all *all, t_imglst **imglst)
{
	t_imglst	*next;

	if (imglst == NULL)
		return ;
	while (*imglst)
	{
		next = (*imglst)->next;
		if ((*imglst)->img != NULL)
			mlx_delete_image(all->mlx, (*imglst)->img);
		free(*imglst);
		*imglst = next;
	}
	*imglst = NULL;
}
