/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:19:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/22 12:40:11 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static float	get_delta_time(t_all *all)
{
	static float	time_for_fps = 0.0f;
	float			delta_time;

	delta_time = mlx_get_time() - all->last_time;
	all->last_time = mlx_get_time();
	time_for_fps += delta_time;
	if (time_for_fps > 1.0f)
	{
		printf("ppr : %i, %5.2f fps\n", all->scene.ppr, 2.0f / delta_time);
		time_for_fps -= 1.0f;
	}
	return (delta_time);
}

static void	ppr_gestion(t_all *all, float delta_time)
{
	static float	time_ignore_input = 0.0f;

	time_ignore_input -= delta_time;
	if (time_ignore_input > 0.0f)
	{
		if (time_ignore_input < 0.0f)
			time_ignore_input = 0.0f;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_EQUAL) && all->scene.ppr < 10
		&& time_ignore_input == 0.0f)
	{
		all->scene.ppr++;
		time_ignore_input = 1.0f;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_MINUS) && all->scene.ppr > 1
		&& time_ignore_input == 0.0f)
	{
		all->scene.ppr--;
		time_ignore_input = 1.0f;
	}
}

void	hook(void *param)
{
	float			delta_time;
	t_all			*all;

	all = param;
	delta_time = get_delta_time(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
	camera_translations(all, delta_time);
	camera_rotations(all, delta_time);
	draw(all);
}

static void	check_param(int argc, char **argv, t_all *all)
{
	if (argc != 2)
	{
		ft_printf_fd("Usage:\n./minirt file.rt\n", 2);
		exit(1);
	}
	all->scene = parse_file(argv[1]);
	if (all->scene.al_intensity == -1.0f || all->scene.camera.fov == 0
		|| all->scene.light.brightness == -1.0f)
	{
		ft_printf_fd("Error\nMinirt : parsing error\n", 2);
		rtlst_free(&all->scene.objects);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_all	all;

	check_param(argc, argv, &all);
	all.last_time = 0.0;
	all.scene.ppr = 4;
	all.ray_tab = alloc_ray_tab();
	if (all.ray_tab == NULL)
	{
		rtlst_free(&all.scene.objects);
		return (EXIT_FAILURE);
	}
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	all.img = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(all.mlx, all.img, 0, 0);
	mlx_loop_hook(all.mlx, &hook, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	rtlst_free(&all.scene.objects);
	free_ray_tab(all.ray_tab, HEIGHT);
	return (EXIT_SUCCESS);
}
