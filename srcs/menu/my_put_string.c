/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_put_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:29:58 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/07 16:44:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	my_put_string(t_all *all, char *text, int x, int y)
{
	t_imglst	*new;

	new = imglst_new(NULL);
	if (new == NULL)
		return ;
	new->img = mlx_put_string(all->mlx, text, x, y);
	imglst_add_back(&all->text_imgs, new);
}
