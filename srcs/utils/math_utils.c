/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:02:29 by aderouba          #+#    #+#             */
/*   Updated: 2023/02/24 15:26:35 by aderouba         ###   ########.fr       */
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

float	equation_minus_result(float a, float b, float discriminant)
{
	return ((-b - sqrt(discriminant)) / (a * 2.0f));
}

float	equation_plus_result(float a, float b, float discriminant)
{
	return ((-b + sqrt(discriminant)) / (a * 2.0f));
}
