/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:19:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/20 09:15:44 by aderouba         ###   ########.fr       */
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
	t_all		*all;
	bool		need_draw;
	const float	rot = 10.0f;
	float	len;

	need_draw = false;
	all = param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
	if (mlx_is_key_down(all->mlx, MLX_KEY_W))
	{
		all->scene.camera.pos = add_vect_vect(&all->scene.camera.pos,
												&all->scene.camera.basis[2]);
		need_draw = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_S))
	{
		all->scene.camera.pos = sub_vect_vect(&all->scene.camera.pos,
												&all->scene.camera.basis[2]);
		need_draw = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_A))
	{
		all->scene.camera.pos = sub_vect_vect(&all->scene.camera.pos,
												&all->scene.camera.basis[0]);
		need_draw = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
	{
		all->scene.camera.pos = add_vect_vect(&all->scene.camera.pos,
												&all->scene.camera.basis[0]);
		need_draw = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_SPACE))
	{
		all->scene.camera.pos = sub_vect_vect(&all->scene.camera.pos,
												&all->scene.camera.basis[1]);
		need_draw = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT_SHIFT))
	{
		all->scene.camera.pos = add_vect_vect(&all->scene.camera.pos,
												&all->scene.camera.basis[1]);
		need_draw = true;
	}

	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
	{
		absolute_rotate(&all->scene.camera.basis[0], rot, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[1], rot, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[2], rot, ROTATE_AROUND_Y);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(&all->scene.camera.basis[2], len);
		need_draw = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
	{
		absolute_rotate(&all->scene.camera.basis[0], -rot, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[1], -rot, ROTATE_AROUND_Y);
		absolute_rotate(&all->scene.camera.basis[2], -rot, ROTATE_AROUND_Y);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(&all->scene.camera.basis[2], len);
		need_draw = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_UP))
	{
		absolute_rotate(&all->scene.camera.basis[0], rot, ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[1], rot, ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[2], rot, ROTATE_AROUND_X);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(&all->scene.camera.basis[2], len);
		need_draw = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_DOWN))
	{
		absolute_rotate(&all->scene.camera.basis[0], -rot, ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[1], -rot, ROTATE_AROUND_X);
		absolute_rotate(&all->scene.camera.basis[2], -rot, ROTATE_AROUND_X);
		len = WIDTH / (tan(all->scene.camera.fov * PI_DIV_360) * 2.0f);
		all->scene.camera.orientation = multiply_vect_number(&all->scene.camera.basis[2], len);
		need_draw = true;
	}

	if (need_draw)
		draw(all, 1);
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

	// Création de la fenêtre
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	all.img = mlx_new_image(all.mlx, WIDTH, HEIGHT);

	// Test de la fonction draw et jolie écran cyan
	draw(&all, 1);
	// render(&all);

	// Initialisation de la fenêtre
	mlx_loop_hook(all.mlx, &hook, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	rtlst_free(&all.scene.objects);

	return (EXIT_SUCCESS);
}
