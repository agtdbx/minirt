/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:02:29 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/27 10:29:11 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

float	calculate_discriminant(float a, float b, float c)
{
	return ((b * b) - (4 * a * c));
}

float	equation_result(float a, float b)
{
	return ((-b) / (a * 2.0f));
}

void	equation_both_result(float a, float b, float discriminant, float *res)
{
	float	srqt_discriminant;
	float	denom;

	srqt_discriminant = sqrt(discriminant);
	denom = 1.0f / (a * 2.0f);
	res[0] = (-b - srqt_discriminant) * denom;
	res[1] = (-b + srqt_discriminant) * denom;
}
