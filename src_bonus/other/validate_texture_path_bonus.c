/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture_path_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:08:26 by mcheragh          #+#    #+#             */
/*   Updated: 2025/03/03 15:14:50 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_valid_texture_path_b(char *path)
{
	int	len;
	int	fd;

	len = ft_strlen(path);
	if (!path || len == 0)
	{
		print_error(RED"Error: Empty texture path\n"RESET);
		return (0);
	}
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		print_error(RED"Error: Texture file must be a .xpm file\n"RESET);
		print_error(RED"%s\n"RESET, path);
		return (0);
	}
	return (1);
}


