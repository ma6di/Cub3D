
#include "cub3d_bonus.h"

bool	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (true);

	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

void	remove_trailing_empty_lines(char **map)
{
	int	last_non_empty;
	int	i;

	last_non_empty = -1;
	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		if (!is_empty_line(map[i]))
			last_non_empty = i;
		i++;
	}
	while (map[++last_non_empty])
	{
		free(map[last_non_empty]);
		map[last_non_empty] = NULL;
	}
}

int	check_empty_line(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && (map[y][x] == ' ' || map[y][x] == '\t'))
			x++;

		if (map[y][x] == '\0')
			return (0);

		y++;
	}
	return (1);
}
