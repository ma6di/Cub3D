/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:58:50 by mcheragh          #+#    #+#             */
/*   Updated: 2025/03/03 15:00:28 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	file_data_order(t_game *game)
{
	if (!game->textures[NORTH].path || \
		!game->textures[SOUTH].path || \
		!game->textures[WEST].path || \
		!game->textures[EAST].path || \
		!game->color[FLOOR].col_tex_str || \
		!game->color[CEILING].col_tex_str)
	{
		print_error(RED"Error: cub file data is not in order or"RESET);
		print_error(RED" one/more texture is missing\n"RESET);
		game->file_order = 1;
	}
}

void	append_map_line(t_game *game, char *line)
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

static void	*str_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
	{
		str++;
	}
	return (str);
}

static void	check_line(char *line, t_game *game)
{
	if (line && ft_strncmp(line, "NO ", 3) == 0)
		game->textures[NORTH].path = ft_strdup(str_start(line + 2));
	else if (line && ft_strncmp(line, "SO ", 3) == 0)
		game->textures[SOUTH].path = ft_strdup(str_start(line + 2));
	else if (line && ft_strncmp(line, "WE ", 3) == 0)
		game->textures[WEST].path = ft_strdup(str_start(line + 2));
	else if (line && ft_strncmp(line, "EA ", 3) == 0)
		game->textures[EAST].path = ft_strdup(str_start(line + 2));
	else if (line && ft_strncmp(line, "F ", 2) == 0)
		game->color[FLOOR].col_tex_str = ft_strdup(str_start(line + 1));
	else if (line && ft_strncmp(line, "C ", 2) == 0)
		game->color[CEILING].col_tex_str = ft_strdup(str_start(line + 1));
	else if (ft_strnstr(line, "111", ft_strlen(line)) && \
		game->map_started == 0)
	{
		file_data_order(game);
		game->map_started = 1;
		append_map_line(game, line);
	}
	else if (ft_strchr("10NSWE \t", line[0]) && game->map_started == 1)
		append_map_line(game, line);
	return ;
}

int	pars_file(const char *filename, t_game *game, char **argv)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error(RED"Error: Could not open file %s\n"RESET, \
				filename), 0);
	if (validate_file(argv[1]) == -1)
	{
		close(fd);
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		check_line(line, game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game->file_order || !validate_cub_elements(game))
		return (0);
	return (1);
}
