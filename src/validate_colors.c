/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:54:21 by mcheragh          #+#    #+#             */
/*   Updated: 2025/03/03 15:17:44 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// Validate color and return a t_color structure with RGB values
int	is_valid_color_texture(t_color *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(color->col_tex_str, ',');
	if (!rgb || two_dim_len(rgb) != 3)
	{
		free_two_dim(rgb);
		return (0);
	}
	if (!is_valid_number(rgb[0]) || !is_valid_number(rgb[1]) || \
		!is_valid_number(rgb[2]))
	{
		free_two_dim(rgb);
		return (0);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_two_dim(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		print_error("Error: Color values must be between 0 and 255\n");
		return (0);
	}
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}
