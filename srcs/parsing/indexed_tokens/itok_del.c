/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itok_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:27:18 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/03 15:32:46 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "libft.h"

void	itok_del(
			t_itok **toks)
{
	if ((*toks)->next != NULL)
		itok_del(&(*toks)->next);
	ft_memdel(&(*toks)->token);
	ft_memdel(toks);
}
