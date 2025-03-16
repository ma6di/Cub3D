/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:19:59 by mcheragh          #+#    #+#             */
/*   Updated: 2025/03/03 15:19:30 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_file(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len > 4)
	{
		if (ft_strncmp(filename + len - 4, ".cub", 4) == 0)
			return (1);
	}
	print_error(RED"Error: File must have a .cub extension\n"RESET);
	return (0);
}

int	validate_colors(t_color *color)
{
	if (!color[FLOOR].col_tex_str || !color[CEILING].col_tex_str)
	{
		print_error(RED"Error: Missing floor or ceiling color (F, C)\n"RESET);
		return (0);
	}
	if (!is_valid_color(&color[FLOOR]))
	{
		print_error(RED"Error: Invalid floor color\n"RESET);
		return (0);
	}
	if (!is_valid_color(&color[CEILING]))
	{
		print_error(RED"Error: Invalid ceiling color\n"RESET);
		return (0);
	}
	return (1);
}

static int	validate_textures(t_texture *textures)
{
	if (!textures[NORTH].path || !textures[SOUTH].path || \
		!textures[WEST].path || !textures[EAST].path || !textures[DOOR].path)
	{
		print_error(RED"Error: Missing one or more textures\n"RESET);
		return (0);
	}
	if (!is_valid_texture_path(textures[NORTH].path) || \
		!is_valid_texture_path(textures[SOUTH].path) \
		|| !is_valid_texture_path(textures[WEST].path) \
		|| !is_valid_texture_path(textures[EAST].path))
		return (0);
	return (1);
}

int	validate_map(t_game *game)
{
	remove_trailing_empty_lines(game->map);
	if (!check_empty_line(game->map))
	{
		print_error(RED"Error: Empty line in map\n"RESET);
		close_window(game);
	}
	cal_map_dim(&game);
	if (!game->map || \
	!is_map_closed_and_accessible(game, game->map, game->height, game->width))
		return (0);
	return (1);
}

int	validate_cub_elements(t_game *game)
{
	if (validate_textures(game->textures) && \
		validate_colors(game->color) && validate_map(game))
		return (1);
	else
		return (0);
}
