/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:19:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/27 13:45:56 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// render function
void	render(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			mlx_put_pixel(all->img, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_image_to_window(all->mlx, all->img, 0, 0);
}

void	hook(void *param)
{
	t_all	*all;

	all = param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
}

int	main(void)
{
	t_ray			ray;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_dst_and_nrm	res_intersect;

	ray.origin = create_vector(0.0f, 0.0f, 0.0f, false);
	ray.direction = create_vector(0.0f, 0.0f, 1.0f, true);
	sphere = create_sphere(create_vector(10.0f, 0.0f, 0.0f, false),
			5.0f, 0XFFFFFFFF);
	plane = create_plane(create_vector(0.0f, 10.0f, 0.0f, false),
			create_vector(0.0f, 1.0f, 0.0f, true),
			0XFFFFFFFF);
	cylinder = create_cylinder(create_vector(0.0f, 0.0f, 10.0f, false),
			create_vector(0.0f, 0.0f, 1.0f, true),
			5.0f,
			10.0f);
	set_cylinder_color(&cylinder, 0XFFFFFFFF);
	res_intersect.dst = -1.0f;
	res_intersect.nrm = create_vector(0.0f, 0.0f, 0.0f, false);
	intersect_sphere(&sphere, &ray, &res_intersect);
	intersect_plane(&plane, &ray, &res_intersect);
	intersect_cylinder(&cylinder, &ray, &res_intersect);
	printf("intersect : %f\n", res_intersect.dst);
	return (EXIT_SUCCESS);
}

// int	main(void)
// {
// 	t_all	all;

// 	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
// 	all.img = mlx_new_image(all.mlx, WIDTH, WIDTH);
// 	render(&all);
// 	mlx_loop_hook(all.mlx, &hook, &all);
// 	mlx_loop(all.mlx);
// 	mlx_terminate(all.mlx);
// 	return (EXIT_SUCCESS);
// }
