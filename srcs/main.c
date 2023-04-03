/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:19:36 by aderouba          #+#    #+#             */
/*   Updated: 2023/04/03 17:36:05 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"

#include <stdlib.h>
#include <unistd.h>

static void		init_struct(t_all *all);
static float	get_delta_time(t_all *all);
void			hook(void *param);

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 2)
	{
		ft_printf_fd("Error\n\nUsage: minirt <%%.rt>\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (parse_file(argv[1], &all.scene) == PARSING_ERROR)
		exit(EXIT_FAILURE);
	// init_struct(&all);
	// all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	// all.img = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(all.mlx, all.img, 0, 0);
	// mlx_loop_hook(all.mlx, &hook, &all);
	// mlx_loop(all.mlx);
	// mlx_terminate(all.mlx);
	// rtlst_free(&all.scene.objects);
	// free_ray_tab(all.ray_tab, HEIGHT);
	// free_color_tab(all.colors_tab, HEIGHT);
	return (EXIT_SUCCESS);
}

static void	init_struct(t_all *all)
{
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
	float			delta_time;
	t_all			*all;

	all = param;
	delta_time = get_delta_time(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
	camera_translations(all, delta_time);
	camera_rotations(all, delta_time);
	ppr_gestion(all, delta_time);
	draw(all);
}
