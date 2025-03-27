#include "cub3d_bonus.h"

int	assign_texture(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->textures[NORTH].path = ft_strdup(str_start_b(line + 2));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->textures[SOUTH].path = ft_strdup(str_start_b(line + 2));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->textures[WEST].path = ft_strdup(str_start_b(line + 2));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->textures[EAST].path = ft_strdup(str_start_b(line + 2));
	else if (ft_strncmp(line, "Z ", 2) == 0)
		game->textures[ZOMBIE].path = ft_strdup(str_start_b(line + 1));
	else
		return (0);
	return (1);
}

int	assign_health_texture(char *line, t_game *game)
{
	if (line && ft_strncmp(line, "H1 ", 3) == 0)
		game->health_bar[0].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "H2 ", 3) == 0)
		game->health_bar[1].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "H3 ", 3) == 0)
		game->health_bar[2].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "H4 ", 3) == 0)
		game->health_bar[3].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "H5 ", 3) == 0)
		game->health_bar[4].path = ft_strdup(str_start_b(line + 2));
	else
		return (0);
	return (1);
}

int	assign_ammo_texture(char *line, t_game *game)
{
	if (line && ft_strncmp(line, "A0 ", 3) == 0)
		game->ammo[0].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A1 ", 3) == 0)
		game->ammo[1].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A2 ", 3) == 0)
		game->ammo[2].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A3 ", 3) == 0)
		game->ammo[3].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A4 ", 3) == 0)
		game->ammo[4].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A5 ", 3) == 0)
		game->ammo[5].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A6 ", 3) == 0)
		game->ammo[6].path = ft_strdup(str_start_b(line + 2));
	else
		return (0);
	return (1);
}

int	assign_heart_texture(char *line, t_game *game)
{
	char	prefix[6];
	int		i;

	if (!line)
		return (0);
	i = 1;
	while (i <= 12)
	{
		snprintf(prefix, sizeof(prefix), "R%d ", i);
		if (ft_strncmp(line, prefix, strlen(prefix)) == 0)
		{
			game->heart_tex[i - 1].path = \
				ft_strdup(str_start_b(line + strlen(prefix)));
			return (1);
		}
		i++;
	}
	return (0);
}

int	assign_c_ammo_texture(char *line, t_game *game)
{
	char	prefix[6];
	int		i;

	if (!line)
		return (0);
	i = 1;
	while (i <= 12)
	{
		snprintf(prefix, sizeof(prefix), "CA%d ", i);
		if (ft_strncmp(line, prefix, strlen(prefix)) == 0)
		{
			game->c_ammo_tex[i - 1].path = \
				ft_strdup(str_start_b(line + strlen(prefix)));
			return (1);
		}
		i++;
	}
	return (0);
}
