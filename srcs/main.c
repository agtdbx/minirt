/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:19:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/27 10:19:47 by aderouba         ###   ########.fr       */
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
	// t_all	all;

	// all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	// all.img = mlx_new_image(all.mlx, WIDTH, WIDTH);
	// render(&all);
	// mlx_loop_hook(all.mlx, &hook, &all);
	// mlx_loop(all.mlx);
	// mlx_terminate(all.mlx);

	t_ray		ray;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;

	ray.origin = create_vector(0.0f, 0.0f, 0.0f, 0);
	ray.direction = create_vector(0.0f, 0.0f, 1.0f, 1);

	sphere = create_sphere(create_vector(10.0f, 0.0f, 0.0f, 0),
							5.0f, 0XFFFFFFFF);

	plane = create_plane(create_vector(0.0f, 10.0f, 0.0f, 0),
							create_vector(0.0f, 1.0f, 0.0f, 1),
							0XFFFFFFFF);

	cylinder = create_cylinder(create_vector(0.0f, 0.0f, 10.0f, 0),
								create_vector(0.0f, 1.0f, 0.0f, 1),
								5.0f,
								10.0f);
	set_cylinder_color(&cylinder, 0XFFFFFFFF);

	printf("sphere   intersect : %f\n", intersect_sphere(&sphere, &ray));
	printf("plane    intersect : %f\n", intersect_plane(&plane, &ray));
	printf("cylinder intersect : %f\n", intersect_cylinder(&cylinder, &ray));

	return (EXIT_SUCCESS);
}
