/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:22:07 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/23 13:19:25 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <memory.h>
# include "MLX42/MLX42.h"
# define WIDTH 1920
# define HEIGHT 1080

# include "libft.h"

// Main struct
typedef struct s_all
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_all;

// main.c
void	render(t_all *all);
void	hook(void *param);
int		main(void);

#endif
