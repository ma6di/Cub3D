
#include "cub3d.h"

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

static int	is_not_enclosed(t_game *game, char **map, int x, int y, int row_len)
{
	char	tile;

	tile = map[y][x];
	if ((tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || \
		tile == 'W') && (x == 0 || y == 0 || \
		x == row_len - 1 || y == game->height - 1 || \
		map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || \
		map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || \
		map[y][x + 1] == '\0' || map[y][x + 1] == '\n'))
	{
		print_error(RED"Error: Map not enclosed at");
		print_error("(%d, %d)\n"RESET, x, game->height - y - 1);
		return (1);
	}
	return (0);
}

int	check_enclosure(t_game *game, char **map)
{
	int	y;
	int	x;
	int	row_len;

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
			if (is_not_enclosed(game, map, x, y, row_len))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}


