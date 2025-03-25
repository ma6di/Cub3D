
#include "cub3d_bonus.h"

void	cal_map_dim_b(t_game **game)
{
	int	height;
	int	width;
	int	line_width;
	int	i;

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

int	first_pos_row_b(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] == ' ')
	{
		i++;
	}
	return (i);
}

int	last_pos_row_b(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	while (len > 0 && line[len - 1] == ' ')
	{
		len--;
	}
	return (len - 1);
}

int	first_pos_col_b(char **map, int col)
{
	int	y;

	y = 0;
	while (map[y] && map[y][col] && map[y][col] == ' ')
	{
		y++;
	}
	return (y);
}

int	last_pos_col_b(char **map, int col, int height)
{
	int	y;

	y = 0;
	while (y < height && map[y] && col < (int)strlen(map[y]) \
			&& map[y][col] == ' ')
	{
		y++;
	}
	while (y < height && map[y] && col < (int)strlen(map[y]) && map[y][col] &&
			(map[y][col] == '1' || map[y][col] == '0' ||
			map[y][col] == 'N' || map[y][col] == 'S' ||
			map[y][col] == 'W' || map[y][col] == 'E' ||
			map[y][col] == 'D' || map[y][col] == 'Z' || 
			map[y][col] == 'H' || map[y][col] == 'K' ||
			map[y][col] == 'A' || map[y][col] == 'F'))
	{
		y++;
	}
	return (y - 1);
}
