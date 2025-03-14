#include "cub3D.h"

int	case_one(t_game *game, char **map, int y)
{
	int first_y;
	int first_y_next;

	first_y = first_pos_row(map[y]);
	first_y_next = first_pos_row(map[y + 1]);
	if (first_y > first_y_next)
	{
		if ((map[y][first_y]) != '1' || (map[y+1][first_y]) != '1')
		{
			print_error("Error: Map not enclosed at (%d, %d)\n", \
				first_y, game->height - y - 1);
			return (0);
		}
	}	
	else if (first_y < first_y_next)
	{
		if ((map[y][first_y_next]) != '1' || (map[y+1][first_y_next]) != '1')
		{
			print_error("Error: Map not enclosed at (%d, %d)\n", \
				first_y, game->height - y - 1);
			return (0);
		}
	}
	return (1);
}

int	case_two(t_game *game, char **map, int y)
{
	int last_y;
	int last_y_next;
	
	last_y = last_pos_row(map[y]);
	last_y_next = last_pos_row(map[y + 1]);
	if ((last_y > last_y_next))
	{
		if ((map[y][last_y_next]) != '1' || (map[y+1][last_y_next]) != '1')
		{
			print_error("Error: Map not enclosed at (%d, %d)\n", \
				last_y_next, game->height - y - 1);
			return (0);
		}
	}
	else if (last_y < last_y_next) 
	{
		if ((map[y][last_y]) != '1' || (map[y+1][last_y]) != '1')
		{
			print_error("Error: Map not enclosed at (%d, %d)\n", \
				last_y, game->height - y - 1);
			return (0);
		}
	}
	return (1);
}

int	case_three(t_game *game, char **map, int x)
{
	int first_x;
	int first_x_next;

	first_x = first_pos_col(map, x);
	first_x_next = first_pos_col(map, x + 1);
	if (first_x < first_x_next)
	{
		if (map[first_x_next] && (map[first_x_next][x] != '1' || \
			map[first_x_next][x + 1] != '1'))
		{
			print_error("Error: Map not enclosed at (%d, %d)\n", x + 1, \
				game->height - first_x_next);
			return (0);
		}
	}
	else if (first_x > first_x_next)
	{
		if (map[first_x] && (map[first_x][x] != '1' || map[first_x][x + 1] != '1'))
		{
			print_error("Error: Map not enclosed at (%d, %d)\n", x, \
				game->height - first_x);
			return (0);
		}
	}
	return (1);
}

int	case_four(t_game *game, char **map, int x)
{
	int last_x;
	int last_x_next;

	last_x = last_pos_col(map, x, game->height);
	last_x_next = last_pos_col(map, x + 1, game->height);
	if (last_x > last_x_next)
	{
		if (last_x_next >= 0 && last_x_next < game->height && map[last_x_next])
		{
			if (x >= 0 && x < strlen(map[last_x_next]) - 1)
			{
				if (map[last_x_next][x] != '1' || map[last_x_next][x + 1] != '1')
				{
					print_error("Error: Map not enclosed at (%d, %d)\n", x, \
						game->height - last_x_next);
					return (0);
				}
			}
			else
				return (1);
		}
		else
			return (1);
	}
	return (1);
}

int	case_five(t_game *game, char **map, int x)
{
	int last_x;
	int last_x_next;

	last_x = last_pos_col(map, x, game->height);
	last_x_next = last_pos_col(map, x + 1, game->height);
	if (last_x < last_x_next)
	{
		if (last_x >= 0 && last_x < game->height && map[last_x])
		{
			if (x >= 0 && x < strlen(map[last_x]) - 1)
			{
				if (map[last_x][x] != '1' || map[last_x][x + 1] != '1')
				{
					print_error("Error: Map not enclosed at (%d, %d)\n", x + 1 , \
						game->height - last_x - 1);
					return (0);
				}
			}
			else
				return (1);
		}
		else
			return (1);
	}
	return(1);
}
	