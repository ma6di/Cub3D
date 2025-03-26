
#include "cub3D.h"


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
void	init_directions(int *dxy)
{
	dxy[0] = 1;
	dxy[1] = 0;
	dxy[2] = -1;
	dxy[3] = 0;
	dxy[4] = 0;
	dxy[5] = 1;
	dxy[6] = 0;
	dxy[7] = -1;
}

t_stack	*init_stack(int size)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->x = malloc(size * sizeof(int));
	stack->y = malloc(size * sizeof(int));
	if (!stack->x || !stack->y)
	{
		free(stack->x);
		free(stack->y);
		free(stack);
		return (NULL);
	}
	stack->size = size;
	stack->top = -1;
	return (stack);
}


void	free_stack(t_stack *stack)
{
	free(stack->x);
	free(stack->y);
	free(stack);
}

//perfroms a floodfill based on on coonected zero's (0) on the map and saves them in **visited
static int	stack_op(t_stack *stack, int *x, int *y, int op)
{
	if (op == PUSH && stack->top + 1 < stack->size)
	{
		stack->top++;
		stack->x[stack->top] = *x;
		stack->y[stack->top] = *y;
		return (1);
	}
	if (op == POP && stack->top >= 0)
	{
		*x = stack->x[stack->top];
		*y = stack->y[stack->top];
		stack->top--;
		return (1);
	}
	return (0);
}

static int	is_valid(t_game *game, int **visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->width || y >= game->height)
		return (0);
	if (!visited[y] || !game->map[y])
		return (0);
	if (visited[y][x] || (game->map[y][x] && game->map[y][x] == '1' ) \
		|| (game->map[y][x] && game->map[y][x] == 'D'))
		return (0);
	return (1);
}

static void	process_flood_fill(t_game *game, int **visited, \
								t_stack *stack, int *dxy)
{
	int	x;
	int	y;
	int	nx;
	int	ny;
	int	i;

	init_directions(dxy);
	while (stack_op(stack, &x, &y, POP))
	{
		if (!is_valid(game, visited, x, y))
			continue ;
		visited[y][x] = 1;
		i = 0;
		while (i < 8)
		{
			nx = x + dxy[i];
			ny = y + dxy[i + 1];
			if (ny < game->height && nx < ft_strlen(game->map[ny]))
			{
				if (is_valid(game, visited, nx, ny))
					stack_op(stack, &nx, &ny, PUSH);
			}
			i += 2;
		}
	}
}

void	flood_fill(t_game *game, int **visited)
{
	t_stack	*stack;
	int		x;
	int		y;
	int		dxy[8];

	stack = init_stack(game->width * game->height);
	if (!stack)
		return ;
	x = game->player.x;
	y = game->player.y;
	stack_op(stack, &x, &y, PUSH);
	process_flood_fill(game, visited, stack, dxy);
	free_stack(stack);
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
int	check_corners(t_game *game, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height - 1)
	{
		if (!case_one(game, map, y, game->height) || \
			!case_two(game, map, y, game->height))
			return (0);
		y++;
	}
	x = 0;
	while (x < game->width - 1)
	{
		if (!case_three(game, map, x, game->height) || \
			!case_four(game, map, x, game->height) \
			|| !case_five(game, map, x, game->height))
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
		!check_corners(game, map))
    {
        free_visited(visited, height);
        return (0);
    }
    free_visited(visited, height);
    return (1);
}
