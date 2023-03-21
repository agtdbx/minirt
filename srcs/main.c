/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:19:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/21 15:51:54 by aderouba         ###   ########.fr       */
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
	static float	time_for_fps = 0.0f;
	static float	time_ignore_input = 0.0f;
	double			delta_time;
	float			len;
	t_all			*all;
	t_vector		tmp;

	all = param;

	delta_time = mlx_get_time() - all->last_time;
	all->last_time = mlx_get_time();

	// Calcule des fps
	time_for_fps += delta_time;
	if (time_for_fps > 1.0f)
	{
		printf("ppr : %i, %5.2f fps\n", all->scene.ppr,  2.0f / delta_time);
		time_for_fps -= 1.0f;
	}

	if (time_ignore_input > 0.0f)
	{
		time_ignore_input -= delta_time;
		if (time_ignore_input < 0.0f)
			time_ignore_input = 0.0f;
	}

	delta_time *= 5.0f;

	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);

	// Mouvement camera
	if (mlx_is_key_down(all->mlx, MLX_KEY_W))
	{
		tmp = multiply_vect_number(&all->scene.camera.basis[2], delta_time);
		all->scene.camera.pos = add_vect_vect(&all->scene.camera.pos,
												&tmp);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_S))
	{
		tmp = multiply_vect_number(&all->scene.camera.basis[2], delta_time);
		all->scene.camera.pos = sub_vect_vect(&all->scene.camera.pos,
												&tmp);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_A))
	{
		tmp = multiply_vect_number(&all->scene.camera.basis[0], delta_time);
		all->scene.camera.pos = sub_vect_vect(&all->scene.camera.pos,
												&tmp);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
	{
		tmp = multiply_vect_number(&all->scene.camera.basis[0], delta_time);
		all->scene.camera.pos = add_vect_vect(&all->scene.camera.pos,
												&tmp);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_SPACE))
	{
		tmp = multiply_vect_number(&all->scene.camera.basis[1], delta_time);
		all->scene.camera.pos = sub_vect_vect(&all->scene.camera.pos,
												&tmp);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT_SHIFT))
	{
		tmp = multiply_vect_number(&all->scene.camera.basis[1], delta_time);
		all->scene.camera.pos = add_vect_vect(&all->scene.camera.pos,
												&tmp);
	}

	// Rotation camera
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
	{
		absolute_rotate(&all->scene.camera.basis[0], (delta_time * 3.0f), ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[1], (delta_time * 3.0f), ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[2], (delta_time * 3.0f), ROTATE_AROUND_Y);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(&all->scene.camera.basis[2], len);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
	{
		absolute_rotate(&all->scene.camera.basis[0], -(delta_time * 3.0f), ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[1], -(delta_time * 3.0f), ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[2], -(delta_time * 3.0f), ROTATE_AROUND_Y);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(&all->scene.camera.basis[2], len);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_UP))
	{
		absolute_rotate(&all->scene.camera.basis[0], (delta_time * 3.0f), ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[1], (delta_time * 3.0f), ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[2], (delta_time * 3.0f), ROTATE_AROUND_X);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(&all->scene.camera.basis[2], len);
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_DOWN))
	{
		absolute_rotate(&all->scene.camera.basis[0], -(delta_time * 3.0f), ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[1], -(delta_time * 3.0f), ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[2], -(delta_time * 3.0f), ROTATE_AROUND_X);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(&all->scene.camera.basis[2], len);
	}

	// Changement ppr
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

	draw(all);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 2)
	{
		ft_printf_fd("Usage:\n./minirt file.rt\n", 2);
		return (1);
	}
	all.scene = parse_file(argv[1]);
	if (all.scene.al_intensity == -1.0f || all.scene.camera.fov == 0
		|| all.scene.light.brightness == -1.0f)
	{
		ft_printf_fd("Error\nMinirt : parsing error\n", 2);
		rtlst_free(&all.scene.objects);
		return (1);
	}
	// Print des paramètres parsés
	printf("\nPARAMETERS :\n\n");
	print_ambiant_light(&all.scene);
	print_camera(&all.scene);
	print_light(&all.scene);
	printf("\n");
	print_rtlst(all.scene.objects);
	printf("\n");

	all.last_time = 0.0;
	all.scene.ppr = 1;
	// Allocation du tableau de rayon
	all.ray_tab = alloc_ray_tab();
	if (all.ray_tab == NULL)
	{
		rtlst_free(&all.scene.objects);
		return (EXIT_FAILURE);
	}

	// Création de la fenêtre
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	all.img = mlx_new_image(all.mlx, WIDTH, HEIGHT);

	mlx_image_to_window(all.mlx, all.img, 0, 0);

	// Initialisation de la fenêtre
	mlx_loop_hook(all.mlx, &hook, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	rtlst_free(&all.scene.objects);

	free_ray_tab(all.ray_tab, HEIGHT);

	return (EXIT_SUCCESS);
}
