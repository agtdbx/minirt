/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:52:58 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/03 11:05:10 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	compute_pixel(t_all *all, t_intersect_ret *res, int x, int y);
static void	set_mouse_pos(t_all *all, int m_pos[2]);

void	calculate_image(t_all *all)
{
	const int		number_ray = WIDTH / all->scene.ppr;
	const int		number_line = HEIGHT / all->scene.ppr;
	int				ray_pos[2];
	int				m_pos[2];
	t_intersect_ret	res;

	set_mouse_pos(all, m_pos);
	fill_tab_ray(all->ray_tab, &all->scene, number_ray, number_line);
	ray_pos[1] = 0;
	while (ray_pos[1] < number_line)
	{
		ray_pos[0] = 0;
		while (ray_pos[0] < number_ray)
		{
			compute_pixel(all, &res, ray_pos[0], ray_pos[1]);
			if (m_pos[0] == ray_pos[0] && m_pos[1] == ray_pos[1])
			{
				all->id_obj_select = res.id;
				mlx_image_to_window(all->mlx, all->img, 0, 0);
			}
			ray_pos[0]++;
		}
		ray_pos[1]++;
	}
	apply_antialiasing(all);
}

static void	compute_pixel(t_all *all, t_intersect_ret *res, int x, int y)
{
	init_intersect_ret(res);
	do_intersections(all, res, &all->ray_tab[y][x]);
	apply_dymamic_light(all, res, &all->ray_tab[y][x], MAX_REFLECT);
	apply_ambiant_light(all, res);
	draw_result(all, res, x, y);
}

void	do_intersections(t_all *all, t_intersect_ret *res, t_ray *ray)
{
	t_rtlst	*obj;

	obj = all->scene.objects;
	while (obj)
	{
		if (obj->type == SPHERE)
			intersect_sphere(&obj->value.as_sphere, ray, res);
		else if (obj->type == PLANE)
			intersect_plane(&obj->value.as_plane, ray, res);
		else if (obj->type == CYLINDER)
			intersect_cylinder(&obj->value.as_cylinder, ray,
				res);
		obj = obj->next;
	}
}

static void	set_mouse_pos(t_all *all, int m_pos[2])
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	if (mlx_is_mouse_down(all->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(all->mlx, &x, &y);
		if (0 <= x && x <= WIDTH - 420 && 0 <= y && y <= HEIGHT)
		{
			x /= all->scene.ppr;
			y /= all->scene.ppr;
		}
	}
	m_pos[0] = x;
	m_pos[1] = y;
}
