/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:12:24 by mcheragh          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/17 15:36:40 by stdi-pum         ###   ########.fr       */
=======
/*   Updated: 2025/03/21 15:32:31 by stdi-pum         ###   ########.fr       */
>>>>>>> mandatory
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int check_walls_b(t_game *game, char **map)
{
<<<<<<< HEAD
    int height = game->height;
    int width = game->width;

=======
    int height;
    int width;

	height = game->height;
    width = game->width;
>>>>>>> mandatory
    // Controlla la penultima riga
    for (int x = 1; x < width - 1; x++)
    {
        if (map[height - 2][x] == '0')
        {
            if (map[height - 1][x - 1] != '1' || map[height - 1][x] != '1' || map[height - 1][x + 1] != '1')
            {
                print_error("Error: Map not enclosed at the last line near (%d, %d)\n", x, height - 1);
                return 0;
            }
        }
    }
<<<<<<< HEAD

=======
>>>>>>> mandatory
    // Controlla la seconda riga
    for (int x = 1; x < width - 1; x++)
    {
        if (map[1][x] == '0')
        {
            if (map[0][x - 1] != '1' || map[0][x] != '1' || map[0][x + 1] != '1')
            {
                print_error("Error: Map not enclosed at the first line near (%d, %d)\n", x, 0);
                return 0;
            }
        }
    }
<<<<<<< HEAD

    return 1;
}

static int	find_player(t_game **game)
=======
    return (1);
}

static int	find_player_b(t_game **game)
>>>>>>> mandatory
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
<<<<<<< HEAD
	flood_fill(game, visited);
	if (!check_accessibility(game, visited) || \
		!check_enclosure(game, map) || \
		!check_corners_b(game, map) || \
		!check_walls_b(game, map))
	{
		free_visited(visited, height);
		return (0);
	}
	free_visited(visited, height);
=======
	flood_fill_b(game, visited);
	// if (!check_accessibility_b(game, visited) || \
	// 	!check_enclosure_b(game, map) || \
	// 	!check_corners_b(game, map) || \
	// 	!check_walls_b(game, map))
	// {
	// 	free_visited_b(visited, height);
	// 	return (0);
	// }
	free_visited_b(visited, height);
>>>>>>> mandatory
	return (1);
}


