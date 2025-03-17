/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:12:24 by mcheragh          #+#    #+#             */
/*   Updated: 2025/03/17 15:36:55 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int check_walls(t_game *game, char **map)
{
    int height = game->height;
    int width = game->width;

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

    return 1;
}

//calculate map dimentions and fills the struct width and height
void cal_map_dim(t_game **game)
{
    int height;
    int width;
    int line_width;
    int i;

    height = 0;
    width = 0;
    while ((*game)->map[height] != NULL)
    {
        line_width = 0;
        i = 0;
        while ((*game)->map[height][i] != '\0')
        {
            line_width++;
            i++;
        }
        if (line_width > width)
            width = line_width;
        height++;
    }
    (*game)->width = width;
    (*game)->height = height;
}

//finds the player position and fills the player x and y and initial direction string
static int find_player(t_game **game)
{
    int x;
    int y;

    if (!game || !(*game) || !(*game)->map)
        return (print_error("Error: Game or map is NULL\n"), 0);

    y = (*game)->height - 1;
    while (y >= 0) // Start from the bottom
    {
        if (!(*game)->map[y]) // Check if row exists
            return (print_error("Error: Invalid map row\n"), 0);

        x = 0;
        while ((*game)->map[y][x] != '\0') // Left to right
        {
            if ((*game)->map[y][x] == 'N' || (*game)->map[y][x] == 'S' ||
                (*game)->map[y][x] == 'E' || (*game)->map[y][x] == 'W')
            {
				(*game)->player.ini_dir = ft_strdup((char[]){(*game)->map[y][x], '\0'});

                (*game)->player.x = x;
                (*game)->player.y = y;
                return (1);
            }
            x++;
        }
        y--;
    }
    print_error("Error: Player not found on the map\n");
    return (0);
}

//checks if the map chars are only 01NSEW and there is only one player
static int validate_map_chars(t_game *game)
{
    int x;
    int y;
    int player_count;

    y = 0;
    player_count = 0;
    while (y < game->height)
    {
        x = 0;
        while (game->map[y][x] != '\0') // Handle line endings correctly
        {
            if (game->map[y][x] == '\n') // Ignore newlines
            {
                x++;
                continue;
            }
            if (ft_strchr("NSEW", game->map[y][x]))
                player_count++;
            else if (!ft_strchr("01NSEW ", game->map[y][x])) // Ensure only valid characters
            {
                print_error("Error: Invalid character '%c' at (%d, %d)\n",
                    game->map[y][x], x, (game->height - 1 - y));
                return (0);
            }
            x++;
        }
        y++;
    }
    if (player_count != 1)
    {
        print_error("Error: Map must contain exactly one player, found %d\n", player_count);
        return (0);
    }
    return (1);
}

//perfroms a floodfill based on on coonected zero's (0) on the map and saves them in **visited 
static void flood_fill(t_game *game, int **visited)
{
    int *stack_x, *stack_y;
    int top, x, y, stack_size;

    stack_size = game->width * game->height;
    stack_x = malloc(stack_size * sizeof(int));
    stack_y = malloc(stack_size * sizeof(int));
    if (!stack_x || !stack_y)
    {
        free(stack_x);
        free(stack_y);
        return;
    }

    top = 0;
    stack_x[top] = game->player.x;
    stack_y[top] = game->player.y;

    while (top >= 0)
    {
        x = stack_x[top];
        y = stack_y[top--];

        if (x < 0 || y < 0 || x >= game->width || y >= game->height)
        {
            print_error("Skipping invalid access at (%d, %d)\n", x, y);
            continue;
        }

        if (visited[y][x] || game->map[y][x] == '1' || game->map[y][x] == '\n')
            continue;

        visited[y][x] = 1;

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < game->width && ny < game->height)
            {
                stack_x[++top] = nx;
                stack_y[top] = ny;
            }
        }
    }
    free(stack_x);
    free(stack_y);
}

static void free_visited(int **visited, int height)
{
    int i;

    i = 0;
    while (i < height)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
}

//compares map 01NSEW with visited aray, if any 
//location in map is not in visited aray, it is unaccesible
static int check_accessibility(t_game *game, int **visited)
{
    int y;
    int x;
    int row_len;
    char tile;

    y = 0;
    x = 0;
    while (y < game->height)
    {
        row_len = 0;
        while (game->map[y][row_len] != '\0') // Handle different row lengths
            row_len++;

        x = 0;
        while (x < row_len)
        {
            tile = game->map[y][x];
            if ((tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W') && !visited[y][x])
            {
                print_error("Error: Inaccessible area found at (%d, %d)\n", x, game->height - y - 1);
                return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}

// Return the position of the first non-space character in each row
int first_pos_row(char *line) 
{
    int i = 0;
    while (line && line[i] && line[i] == ' ')
    {
        i++;
    }
    return i;
}

// Return the position of the last non-space character in each row
int last_pos_row(char *line) 
{
    int i = 0;
    int len = ft_strlen(line); // Get the total length of the row
    while (len > 0 && line[len - 1] == ' ')  // Skip trailing spaces
    {
        len--;
    }
    return len - 1; 
}

// Return the position of the first non-space character in each column
int first_pos_col(char **map, int col)
{
    int y = 0;
    while (map[y][col] && map[y][col] == ' ')
    {
		y++;
    }
    return y;
}

// Return the position of the last non-space character in each column
int last_pos_col(char **map, int col, int height)
{
    int y;
	
	y = 0;
    while (y < height && map[y] && col < (int)strlen(map[y]) && map[y][col] == ' ')
    {
        y++;
    }
    while (y < height && map[y] && col < (int)strlen(map[y]) && map[y][col] &&
          (map[y][col] == '1' || map[y][col] == '0' ||
           map[y][col] == 'N' || map[y][col] == 'S' ||
           map[y][col] == 'W' || map[y][col] == 'E' ))
    {
        y++;
    }
    return (y - 1);
}

//since map is not rectangular and space in map is valid, it checks all 90 degree corners
//for unclose map
static int check_corners(t_game *game, char **map)
{
	int y;
	int x;

	y = 0;
    while (y < game->height - 1)
    {
		if(!case_one(game, map, y) || !case_two(game, map, y))
			return (0);
        y++;
	}
	x = 0;
	while (x < game->width)
	{
		if(!case_three(game, map, x) || !case_four(game, map, x) || !case_four(game, map, x))
			return (0);
		x++;
	}
    return (1);
}

//check the srounding postions of 01NSEW for unclosed map
static int check_enclosure(t_game *game, char **map)
{
    int row_len;
    int x;
    char tile;
    int y;

    y = 0;
    while (y < game->height)
    {
        row_len = 0;
        while (map[y][row_len] != '\0')
            row_len++;
        if (map[y][row_len - 1] == '\n')
            row_len--;
        x = 0;
        while (x < row_len)
        {
            tile = map[y][x];
            if ((tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W') &&
                (x == 0 || y == 0 || x == row_len - 1 || y == game->height - 1 ||
                 map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
                 map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || map[y][x + 1] == '\0' || 
				map[y][x + 1] == '\n'))
            {
                print_error("Error9: Map not enclosed at (%d, %d)\n", x, game->height - y - 1);
                return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}

int is_map_closed_and_accessible(t_game *game, char **map, int height, int width)
{
	int y;
	int **visited;

	y = 0;
    if (!find_player(&game))
        return (0);
    if (!validate_map_chars(game))
        return (0);
    visited = malloc(height * sizeof(int *));
    if (!visited)
        return (0);
	while (y < height)
	{
		visited[y] = ft_calloc(width, sizeof(int));
		if (!visited[y])
		{
			free_visited(visited, y);
			return (0);
		}
		y++;
	}
    flood_fill(game, visited);
    if (!check_accessibility(game, visited) || !check_enclosure(game, map) || 
		!check_corners(game, map) || \
		!check_walls(game, map))
    {
        free_visited(visited, height);
        return (0);
    }
    free_visited(visited, height);
    return (1);
}