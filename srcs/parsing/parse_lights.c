/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:42:29 by aderouba          #+#    #+#             */
/*   Updated: 2023/05/19 12:57:01 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdbool.h>

#include "libft.h"

static void		compute_intensity(t_light *ret_light);
static t_result	parse_brightness(char const *nptr, float *ret_brightness);

t_result	parse_ambient_light(t_scene *ret_scene)
{
	static bool	is_initialized = false;
	char		*tok;

	if (is_initialized)
		return (FAILURE);
	is_initialized = true;
	tok = ft_strtok(NULL, " \n");
	if (parse_brightness(tok, &ret_scene->ambient_light.brightness) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_color(tok, &ret_scene->ambient_light.color) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (tok != NULL)
		return (FAILURE);
	compute_intensity(&ret_scene->ambient_light);
	return (SUCCESS);
}

t_result	parse_light(t_scene *ret_scene)
{
	static int	id = -4;
	t_vec3		pos;
	float		brightness;
	t_color		color;
	t_light		*new_light;
	t_light		*tmp;
	char		*tok;

	tok = ft_strtok(NULL, " \n");
	if (parse_vec(tok, &pos) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_brightness(tok, &brightness) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_color(tok, &color) == FAILURE)
		return (FAILURE);
	if (ft_strtok(NULL, " \n") != NULL)
		return (FAILURE);
	new_light = malloc(sizeof(t_light));
	if (new_light == NULL)
		return (FAILURE);
	vec3_dup(&new_light->pos, &pos);
	new_light->color = color;
	new_light->brightness = brightness;
	new_light->id = id;
	new_light->next = NULL;
	compute_intensity(new_light);
	id--;
	tmp = ret_scene->lights;
	if (tmp == NULL)
	{
		ret_scene->lights = new_light;
		return (SUCCESS);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_light;
	return (SUCCESS);
}

static t_result	parse_brightness(char const *nptr, float *ret_brightness)
{
	if (is_float(nptr) == false)
		return (FAILURE);
	*ret_brightness = ft_atof(nptr);
	if (*ret_brightness < 0.0f || 1.0f < *ret_brightness)
		return (FAILURE);
	return (SUCCESS);
}

static void	compute_intensity(t_light *ret_light)
{
	ret_light->intensity_r = ret_light->color.r / 255.0f;
	ret_light->intensity_g = ret_light->color.g / 255.0f;
	ret_light->intensity_b = ret_light->color.b / 255.0f;
}
