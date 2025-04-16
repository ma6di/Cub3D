/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:54:21 by mcheragh          #+#    #+#             */
/*   Updated: 2025/04/02 16:30:45 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	trim_trailing_spaces(char **rgb)
{
	int		i;
	int		len;

	if (!rgb)
		return ;
	i = 0;
	while (rgb[i])
	{
		len = ft_strlen(rgb[i]);
		while (len > 0 && ft_isspace((unsigned char)rgb[i][len - 1]))
		{
			rgb[i][len - 1] = '\0';
			len--;
		}
		i++;
	}
}

static int	is_valid_number_b(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_rgb_str_b(char **rgb)
{
	if (!rgb || two_dim_len_b(rgb) != 3)
	{
		print_error(RED"Error: Invalid color format\n"RESET);
		free_two_dim_b(rgb);
		return (0);
	}
	if (!is_valid_number_b(rgb[0]) || !is_valid_number_b(rgb[1]) || \
		!is_valid_number_b(rgb[2]))
	{
		print_error(RED"Error: Color values must be numbers\n"RESET);
		free_two_dim_b(rgb);
		return (0);
	}
	return (1);
}

static int	parse_rgb_b(t_color *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	color->mode = 1;
	rgb = ft_split(color->col_tex_str, ',');
	trim_trailing_spaces(rgb);
	if (!check_rgb_str_b(rgb))
		return (0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_two_dim_b(rgb);
		print_error(RED"Error: Color values must be between 0 and 255\n"RESET);
		return (0);
	}
	free_two_dim_b(rgb);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}

int	is_valid_color_texture_b(t_color *color)
{
	if (ft_strchr(color->col_tex_str, '/') != NULL && \
		ft_strncmp(color->col_tex_str, ".xpm", ft_strlen(color->col_tex_str)))
	{
		if (!is_valid_texture_path_b(color->col_tex_str))
			return (0);
		color->mode = 2;
	}
	else
	{
		if (!parse_rgb_b(color))
			return (0);
	}
	return (1);
}
