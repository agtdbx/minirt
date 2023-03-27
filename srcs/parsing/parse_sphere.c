/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:08:01 by tdubois           #+#    #+#             */
/*   Updated: 2023/03/27 18:43:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdbool.h>

#include "libft.h"

static t_result	parse_radius(char const *nptr, float *ret_radius);

t_result	parse_sphere(t_scene *scene)
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
	if (parse_radius(tok, &radius) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_color(tok, &color) == FAILURE)
		return (FAILURE);
	if (ft_strtok(NULL, " \n") != NULL)
		return (FAILURE);
	sphere = rtlst_new(SPHERE, (t_rtlst_v)create_sphere(pos, radius, color));
	if (sphere == NULL)
		return (FAILURE);
	rtlst_add_back(&scene->objects, sphere);
	return (SUCCESS);
}

static t_result	parse_radius(char const *nptr, float *ret_radius)
{
	if (is_float(nptr) == false)
		return (FAILURE);
	*ret_radius = ft_atof(nptr);
	return (SUCCESS);
}
