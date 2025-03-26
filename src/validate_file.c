/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:58:15 by mcheragh          #+#    #+#             */
/*   Updated: 2025/02/19 16:17:50 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Check if the file has a `.cub` extension
static int	is_cub_file(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	return (len > 4 && ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

// Open and validate the file
int	validate_file(const char *filename)
{
	if (!is_cub_file(filename))
	{
		print_error("Error: File must have a .cub extension\n");
		return (-1);
	}
	return (1);
}
