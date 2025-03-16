/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:12:24 by mcheragh          #+#    #+#             */
/*   Updated: 2025/03/03 16:22:23 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	find_player_b(t_game **game)
{
	int	x;
	int	y;

	y = (*game)->height - 1;
	while (y >= 0)
	{
		x = 0;
		while ((*game)->map[y][x] != '\0')
		{
			if ((*game)->map[y][x] == 'N' || (*game)->map[y][x] == 'S' ||
				(*game)->map[y][x] == 'E' || (*game)->map[y][x] == 'W')
			{
				(*game)->player.ini_dir = malloc(2 * sizeof(char));
				(*game)->player.ini_dir[0] = (*game)->map[y][x];
				(*game)->player.ini_dir[1] = '\0';
				(*game)->player.x = x + 0.5;
				(*game)->player.y = y + 0.5;
				return (1);
			}
			x++;
		}
		y--;
	}
	print_error(RED"Error: Player not found on the map\n"RESET);
	return (0);
}

static int	**allocate_visited_b(int height, int width)
{
	int	y;
	int	**visited;

	visited = malloc(height * sizeof(int *));
	if (!visited)
		return (NULL);
	y = 0;
	while (y < height)
	{
		visited[y] = ft_calloc(width, sizeof(int));
		if (!visited[y])
		{
			free_visited_b(visited, y);
			return (NULL);
		}
		y++;
	}
	return (visited);
}

int	is_map_closed_and_accessible_b(t_game *game, char **map, \
								int height, int width)
{
	int	**visited;

	if (!game || !map)
	{
		print_error(RED"Error: Game or map is NULL\n"RESET);
		return (0);
	}
	if (!find_player_b(&game) || !validate_map_chars_b(game))
		return (0);
	visited = allocate_visited_b(height, width);
	if (!visited)
		return (0);
	flood_fill_b(game, visited);
	if (!check_accessibility_b(game, visited) || \
		!check_enclosure_b(game, map) || \
		!check_corners_b(game, map))
	{
		free_visited_b(visited, height);
		return (0);
	}
	free_visited_b(visited, height);
	return (1);
}

