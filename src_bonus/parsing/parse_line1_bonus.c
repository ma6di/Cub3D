#include "cub3d_bonus.h"

static int	assign_key_texture(char *line, t_game *game)
{
	if (line && ft_strncmp(line, "K1 ", 3) == 0)
		game->key_tex[0].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "K2 ", 3) == 0)
		game->key_tex[1].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "K3 ", 3) == 0)
		game->key_tex[2].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "K4 ", 3) == 0)
		game->key_tex[3].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "K5 ", 3) == 0)
		game->key_tex[4].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "K6 ", 3) == 0)
		game->key_tex[5].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "K7 ", 3) == 0)
		game->key_tex[6].path = ft_strdup(str_start_b(line + 2));
	else
		return (0);
	return (0);
}

static int	assign_door_texture(char *line, t_game *game)
{
	if (line && ft_strncmp(line, "D1 ", 3) == 0)
		game->textures[DOOR_1].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "D2 ", 3) == 0)
		game->textures[DOOR_2].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "D3 ", 3) == 0)
		game->textures[DOOR_3].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "D4 ", 3) == 0)
		game->textures[DOOR_4].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "D5 ", 3) == 0)
		game->textures[DOOR_5].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "D6 ", 3) == 0)
		game->textures[DOOR_6].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "END ", 4) == 0)
		game->textures[FINAL_DOOR].path = ft_strdup(str_start_b(line + 3));
	else
		return (0);
	return (1);
}

static int	assign_gun_texture(char *line, t_game *game)
{
	if (ft_strncmp(line, "G ", 2) == 0)
		game->gun[GUN].path = ft_strdup(str_start_b(line + 1));
	else if (ft_strncmp(line, "GS ", 3) == 0)
		game->gun[GUN_SHUT].path = ft_strdup(str_start_b(line + 2));
	else
		return (0);
	return (1);
}

static int	assign_color_texture(char *line, t_game *game)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		game->color[FLOOR].col_tex_str = ft_strdup(str_start_b(line + 1));
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->color[CEILING].col_tex_str = ft_strdup(str_start_b(line + 1));
	else if (ft_strncmp(line, "SK ", 3) == 0)
		game->color[SKY].col_tex_str = ft_strdup(str_start_b(line + 2));
	else
		return (0);
	return (1);
}

int	check_line_b(char *line, t_game *game)
{
	if (!line)
		return (1);
	if (assign_texture(line, game) || assign_health_texture(line, game) || \
		assign_ammo_texture(line, game) || assign_heart_texture(line, game) || \
		assign_c_ammo_texture(line, game) || assign_key_texture(line, game) || \
		assign_door_texture(line, game) || assign_gun_texture(line, game) || \
		assign_color_texture(line, game))
	{
		return (1);
	}
	else if (ft_strnstr(line, "1111", ft_strlen(line)) && \
					game->map_started == 0)
	{
		file_data_order_b(game);
		game->map_started = 1;
		append_map_line_b(game, line);
	}
	else if (ft_strchr("10NSWEDZ \t", line[0]) && game->map_started == 1)
		append_map_line_b(game, line);
	return (1);
}
