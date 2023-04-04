/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:42:29 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/04 14:13:36 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdbool.h>

#include "libft.h"

// static void		compute_intensity(t_light *ret_light);
// static t_result	parse_brightness(char const *nptr, float *ret_brightness);

// t_result	parse_ambient_light(t_scene *ret_scene)
// {
// 	static bool	is_initialized = false;
// 	char		*tok;
//
// 	if (is_initialized)
// 		return (FAILURE);
// 	is_initialized = true;
// 	tok = ft_strtok(NULL, " \n");
// 	if (parse_brightness(tok, &ret_scene->ambient_light.brightness) == FAILURE)
// 		return (FAILURE);
// 	tok = ft_strtok(NULL, " \n");
// 	if (parse_color(tok, &ret_scene->ambient_light.color) == FAILURE)
// 		return (FAILURE);
// 	tok = ft_strtok(NULL, " \n");
// 	if (tok != NULL)
// 		return (FAILURE);
// 	compute_intensity(&ret_scene->ambient_light);
// 	return (SUCCESS);
// }

// t_result	parse_light(t_scene *ret_scene)
// {
// 	static bool	is_initialized = false;
// 	char		*tok;
//
// 	if (is_initialized)
// 		return (FAILURE);
// 	is_initialized = true;
// 	tok = ft_strtok(NULL, " \n");
// 	if (parse_vec(tok, &ret_scene->light.pos) == FAILURE)
// 		return (FAILURE);
// 	tok = ft_strtok(NULL, " \n");
// 	if (parse_brightness(tok, &ret_scene->light.brightness) == FAILURE)
// 		return (FAILURE);
// 	tok = ft_strtok(NULL, " \n");
// 	if (parse_color(tok, &ret_scene->light.color) == FAILURE)
// 		return (FAILURE);
// 	if (ft_strtok(NULL, " \n") != NULL)
// 		return (FAILURE);
// 	compute_intensity(&ret_scene->light);
// 	return (SUCCESS);
// }

// static t_result	parse_brightness(char const *nptr, float *ret_brightness)
// {
// 	if (is_float(nptr) == false)
// 		return (FAILURE);
// 	*ret_brightness = ft_atof(nptr);
// 	if (*ret_brightness < 0.0f || 1.0f < *ret_brightness)
// 		return (FAILURE);
// 	return (SUCCESS);
// }

static void	compute_intensity(t_light *ret_light)
{
	ret_light->intensity_r = ret_light->color.r / 255.0f;
	ret_light->intensity_g = ret_light->color.g / 255.0f;
	ret_light->intensity_b = ret_light->color.b / 255.0f;
}
