/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:14:29 by tdubois           #+#    #+#             */
/*   Updated: 2023/03/28 12:26:10 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include "libft.h"

static t_result	parse_fov(char const *fov_str, int *ret_fov);

t_result	parse_camera(t_scene *ret_scene)
{
	static bool	is_initialized = false;
	char		*tok;

	if (is_initialized)
		return (FAILURE);
	is_initialized = true;
	tok = ft_strtok(NULL, " \n");
	if (parse_vec(tok, &ret_scene->camera.pos) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_direction(tok, &ret_scene->camera.basis[2]) == FAILURE)
		return (FAILURE);
	tok = ft_strtok(NULL, " \n");
	if (parse_fov(tok, &ret_scene->camera.fov) == FAILURE)
		return (FAILURE);
	if (ft_strtok(NULL, " \n") != NULL)
		return (FAILURE);
	compute_screen_basis(&ret_scene->camera);
	return (SUCCESS);
}

static t_result	parse_fov(char const *fov_str, int *ret_fov)
{
	if (is_int(fov_str) == false)
		return (FAILURE);
	*ret_fov = ft_atoi(fov_str);
	if (*ret_fov < 0 || 180 < *ret_fov)
		return (FAILURE);
	return (SUCCESS);
}
