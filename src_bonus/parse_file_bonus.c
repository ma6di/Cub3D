/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:58:50 by mcheragh          #+#    #+#             */
/*   Updated: 2025/03/03 15:05:38 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	append_map_line_b(t_game *game, char *line)
{
	int		i;
	char	**new_map;

	i = 0;
	while (game->map && game->map[i])
		i++;
	new_map = malloc((i + 2) * sizeof(char *));
	if (!new_map)
		return ;
	i = 0;
	while (game->map && game->map[i])
	{
		new_map[i] = game->map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
	{
		free(new_map);
		return ;
	}
	new_map[i + 1] = NULL;
	free(game->map);
	game->map = new_map;
}

char	*str_start_b(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;

	return (str);
}

void	file_data_order_b(t_game *game)
{
	if (!game->textures[NORTH].path || \
		!game->textures[SOUTH].path || \
		!game->textures[WEST].path || \
		!game->textures[EAST].path || \
		!game->color[FLOOR].col_tex_str || \
		(!game->color[CEILING].col_tex_str && \
		!game->color[SKY].col_tex_str) ||
		!game->gun[GUN].path || 
		!game->textures[ZOMBIE].path)
	{
		print_error(RED"Error: cub file data is not in order\n"RESET);
		game->file_order = 1;
	}
}

static int	check_line_b(char *line, t_game *game)
{
	if (line && ft_strncmp(line, "NO ", 3) == 0)
		game->textures[NORTH].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "SO ", 3) == 0)
		game->textures[SOUTH].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "WE ", 3) == 0)
		game->textures[WEST].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "EA ", 3) == 0)
		game->textures[EAST].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "H1 ", 3) == 0)
		game->health_bar[0].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "H2 ", 3) == 0)
		game->health_bar[1].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "H3 ", 3) == 0)
		game->health_bar[2].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "H4 ", 3) == 0)
		game->health_bar[3].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "H5 ", 3) == 0)
		game->health_bar[4].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A0 ", 3) == 0)
		game->armor[0].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A1 ", 3) == 0)
		game->armor[1].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A2 ", 3) == 0)
		game->armor[2].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A3 ", 3) == 0)
		game->armor[3].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A4 ", 3) == 0)
		game->armor[4].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A5 ", 3) == 0)
		game->armor[5].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "A6 ", 3) == 0)
		game->armor[6].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "R1 ", 3) == 0)
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
	else if (line && ft_strncmp(line, "D ", 2) == 0)
		game->textures[DOOR].path = ft_strdup(str_start_b(line + 1));
	else if (line && ft_strncmp(line, "Z ", 2) == 0)
		game->textures[ZOMBIE].path = ft_strdup(str_start_b(line + 1));
	else if (line && ft_strncmp(line, "G ", 2) == 0)
		game->gun[GUN].path = ft_strdup(str_start_b(line + 1));
	else if (line && ft_strncmp(line, "GS ", 3) == 0)
		game->gun[GUN_SHUT].path = ft_strdup(str_start_b(line + 2));
	else if (line && ft_strncmp(line, "F ", 2) == 0)
		game->color[FLOOR].col_tex_str = ft_strdup(str_start_b(line + 1));
	else if (line && ft_strncmp(line, "C ", 2) == 0)
		game->color[CEILING].col_tex_str = ft_strdup(str_start_b(line + 1));
	else if (line && ft_strncmp(line, "SK ", 3) == 0)
		game->color[SKY].col_tex_str = ft_strdup(str_start_b(line + 2));
	else if (line && (ft_strnstr(line, "1111", ft_strlen(line))) && \
			game->map_statred == 0)
	{
		file_data_order_b(game);
		game->map_statred = 1;
		append_map_line_b(game, line);
	}
	else if (line && (ft_strchr("10NSWEDZ \t", line[0])) && \
			game->map_statred == 1)
		append_map_line_b(game, line);
	return (1);
}

int	pars_file_b(const char *filename, t_game *game, char **argv)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(RED"Error: Could not open file %s\n"RESET, filename);
		return (0);
	}
	if (!validate_file_b(argv[1]))
	{
		close(fd);
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		check_line_b(line, game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game->file_order || !validate_cub_elements_b(game))
		close_window_b(game);
	return (1);
}
