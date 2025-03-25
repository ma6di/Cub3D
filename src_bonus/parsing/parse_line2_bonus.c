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
	if (line && ft_strncmp(line, "R1 ", 3) == 0)
		game->heart_tex[0].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R2 ", 3) == 0)
		game->heart_tex[1].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R3 ", 3) == 0)
		game->heart_tex[2].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R4 ", 3) == 0)
		game->heart_tex[3].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R5 ", 3) == 0)
		game->heart_tex[4].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R6 ", 3) == 0)
		game->heart_tex[5].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R7 ", 3) == 0)
		game->heart_tex[6].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R8 ", 3) == 0)
		game->heart_tex[7].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R9 ", 3) == 0)
		game->heart_tex[8].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R10 ", 3) == 0)
		game->heart_tex[9].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "R11 ", 4) == 0)
		game->heart_tex[10].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "R12 ", 4) == 0)
		game->heart_tex[11].path = ft_strdup(str_start_b(line + 3));
	else
		return (0);
	return (1);
}

int	assign_c_ammo_texture(char *line, t_game *game)
{
	if (line && ft_strncmp(line, "CA1 ", 4) == 0)
		game->c_ammo_tex[0].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "CA2 ", 4) == 0)
		game->c_ammo_tex[1].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "CA3 ", 4) == 0)
		game->c_ammo_tex[2].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "CA4 ", 4) == 0)
		game->c_ammo_tex[3].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "CA5 ", 4) == 0)
		game->c_ammo_tex[4].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "CA6 ", 4) == 0)
		game->c_ammo_tex[5].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "CA7 ", 4) == 0)
		game->c_ammo_tex[6].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "CA8 ", 4) == 0)
		game->c_ammo_tex[7].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "CA9 ", 4) == 0)
		game->c_ammo_tex[8].path = ft_strdup(str_start_b(line + 3));
	else if (line && ft_strncmp(line, "CA10 ", 5) == 0)
		game->c_ammo_tex[9].path = ft_strdup(str_start_b(line + 4));
	else if (line && ft_strncmp(line, "CA11 ", 5) == 0)
		game->c_ammo_tex[10].path = ft_strdup(str_start_b(line + 4));
	else if (line && ft_strncmp(line, "CA12 ", 5) == 0)
		game->c_ammo_tex[11].path = ft_strdup(str_start_b(line + 4));
	else
		return (0);
	return (1);
}
