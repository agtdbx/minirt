/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:08:01 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/05 13:19:26 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdbool.h>

#include "libft.h"

t_result	parse_sphere(t_scene *ret_scene)
{
	t_rtlst		*sphere;
	char		*tok;
	float		radius;
	t_color		color;
	t_vector	pos;

	tok = ft_strtok(NULL, " \n");
	if (parse_vec(tok, &pos) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_float(tok, &radius) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_color(tok, &color) == FAILURE)
		return (FAILURE);
	if (ft_strtok(NULL, " \n") != NULL)
		return (FAILURE);
	sphere = rtlst_new(SPHERE, (t_rtlst_v)create_sphere(pos, radius, color));
	if (sphere == NULL)
		return (FAILURE);
	rtlst_add_back(&ret_scene->objects, sphere);
	return (SUCCESS);
}
