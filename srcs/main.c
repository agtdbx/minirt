/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:19:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/03 16:14:17 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdlib.h>
#include <unistd.h>

static void		init_struct(t_all *all);
static float	get_delta_time(t_all *all);
void			hook(void *param);
static void		set_mouse_state(t_all *all);

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 2)
	{
		ft_printf_fd("Error\nUsage: minirt file.rt\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (parse_file(argv[1], &all.scene) == FAILURE)
	{
		ft_printf_fd("Error\nParsing error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	init_struct(&all);
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	all.img = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	mlx_set_window_pos(all.mlx, 0, 0);
	mlx_image_to_window(all.mlx, all.img, 0, 0);
	mlx_set_window_title(all.mlx, "minirt");
	mlx_loop_hook(all.mlx, &hook, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	rtlst_free(&all.scene.objects);
	free_ray_tab(all.ray_tab, HEIGHT);
	free_color_tab(all.colors_tab, HEIGHT);
	return (EXIT_SUCCESS);
}

static void	init_struct(t_all *all)
{
	init_menu(all);
	all->show_menu = false;
	all->last_time = 0.0;
	all->scene.ppr = 1;
	all->ray_tab = alloc_ray_tab();
	if (all->ray_tab == NULL)
	{
		rtlst_free(&all->scene.objects);
		exit(EXIT_FAILURE);
	}
	all->colors_tab = alloc_color_tab();
	if (all->colors_tab == NULL)
	{
		rtlst_free(&all->scene.objects);
		free_ray_tab(all->ray_tab, HEIGHT);
		exit(EXIT_FAILURE);
	}
}

static float	get_delta_time(t_all *all)
{
	static float	time_for_fps = 0.0f;
	float			delta_time;

	delta_time = mlx_get_time() - all->last_time;
	all->last_time = mlx_get_time();
	time_for_fps += delta_time;
	if (time_for_fps > 1.0f)
	{
		printf("ppr : %i, %5.2f fps\n", all->scene.ppr, 1.0f / delta_time);
		time_for_fps -= 1.0f;
	}
	return (delta_time);
}

void	hook(void *param)
{
	float	delta_time;
	t_all	*all;

	all = param;
	delta_time = get_delta_time(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
	camera_translations(all, delta_time);
	camera_rotations(all, delta_time);
	ppr_gestion(all, delta_time);
	check_tab_pressed(all, delta_time);
	set_mouse_state(all);
	calculate_image(all);
	if (all->show_menu)
		draw_menu(all);
}

static void	set_mouse_state(t_all *all)
{
	mlx_get_mouse_pos(all->mlx, &all->mouse.x, &all->mouse.y);
	if (mlx_is_mouse_down(all->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		all->mouse.pressed = true;
		if (0 <= all->mouse.x && all->mouse.x <= WIDTH - 420
			&& 0 <= all->mouse.y && all->mouse.y <= HEIGHT)
		{
			all->mouse.tab_x = all->mouse.x / all->scene.ppr;
			all->mouse.tab_y = all->mouse.y / all->scene.ppr;
		}
	}
	else
		all->mouse.pressed = false;
}
