/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:48 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/02 11:46:46 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	get_nb(char *nbr);
static bool	get_fnb(char *nbr, float *nb, float min, float max);

// return 0 in case of error.
// return color if good
int	parse_color(char *part)
{
	char	*saveptr;
	char	*word;
	int		color[3];
	int		nb;
	int		i;

	i = 0;
	while (i < 3)
	{
		if (i == 0)
			word = ft_strtok_r(part, ",", &saveptr);
		else
			word = ft_strtok_r(NULL, ",", &saveptr);
		nb = get_nb(word);
		if (nb == -1)
			return (0);
		color[i] = nb;
		i++;
	}
	word = ft_strtok_r(NULL, ",", &saveptr);
	if (word != NULL)
		return (0);
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | 255);
}

static int	get_nb(char *nbr)
{
	int	nb;

	if (!nbr)
		return (-1);
	if (!is_int(nbr))
		return (-1);
	nb = ft_atoi(nbr);
	if (nb < 0 || nb > 255)
		return (-1);
	return (nb);
}

bool	parse_vector(char *part, float *nbs, float min, float max)
{
	char	*saveptr;
	char	*word;
	float	nb;
	int		i;

	i = 0;
	while (i < 3)
	{
		if (i == 0)
			word = ft_strtok_r(part, ",", &saveptr);
		else
			word = ft_strtok_r(NULL, ",", &saveptr);
		if (!get_fnb(word, &nb, min, max))
			return (false);
		nbs[i] = nb;
		i++;
	}
	word = ft_strtok_r(NULL, ",", &saveptr);
	if (word != NULL)
		return (false);
	return (true);
}

static bool	get_fnb(char *nbr, float *nb, float min, float max)
{
	if (nbr == NULL)
		return (false);
	if (!is_float(nbr))
		return (false);
	*nb = ft_atof(nbr);
	if (min != max && (*nb < min || *nb > max))
		return (false);
	return (true);
}
