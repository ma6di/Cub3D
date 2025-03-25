#include "cub3d_bonus.h"

void	init_mlx_wall_texture_b(t_game *game, int index, char *path)
{
	if (!path)
	{
		print_error(RED"WALL Texture path is NULL\n"RESET);
		return ;
	}
	game->textures[index].img = mlx_xpm_file_to_image(\
		game->mlx, path, &(game->textures[index].width), \
		&(game->textures[index].height));
	if (!game->textures[index].img)
	{
		print_error(RED"Texture file could not be loaded: ");
		print_error("%s\n"RESET, path);
		close_window_b(game);
	}
	game->textures[index].addr = mlx_get_data_addr(\
		game->textures[index].img, &game->textures[index].bpp, \
		&game->textures[index].line_len, &game->textures[index].endian);
	if (!game->textures[index].addr)
	{
		print_error(RED"Error: Texture %d address is NULL!\n"RESET, index);
		close_window_b(game);
	}
}

void	init_mlx_health_bar_texture_b(t_game *game)
{
	int index;
	char *path;

	index = 0;
	while (index < 5)
	{
		if (!game->health_bar[index].path)
		{
			print_error(RED"Health bar Texture %d path is NULL\n"RESET, index);
			return ;
		}
		path = game->health_bar[index].path;
		game->health_bar[index].img = mlx_xpm_file_to_image(\
			game->mlx, path, &(game->health_bar[index].width), \
			&(game->health_bar[index].height));
		if (!game->health_bar[index].img)
		{
			print_error(RED"Error: health bar Texture file could not be loaded: ");
			print_error("%s\n"RESET, path);
			close_window_b(game);
		}
		game->health_bar[index].addr = mlx_get_data_addr(\
			game->health_bar[index].img, &game->health_bar[index].bpp, \
			&game->health_bar[index].line_len, &game->health_bar[index].endian);
		if (!game->health_bar[index].addr)
		{
			print_error(RED"Error: Health bar texture %d address is NULL!\n"RESET, index);
			close_window_b(game);
		}
		index++;
	}
}

void	init_mlx_ammo_bar_texture_b(t_game *game)
{
	int index;
	char *path;

	index = 0;
	while (index < 7)
	{
		if (!game->ammo[index].path)
		{
			print_error(RED"ammo bar Texture %d path is NULL\n"RESET, index);
			return ;
		}
		path = game->ammo[index].path;
		game->ammo[index].img = mlx_xpm_file_to_image(\
			game->mlx, path, &(game->ammo[index].width), \
			&(game->ammo[index].height));
		if (!game->ammo[index].img)
		{
			print_error(RED"Error: ammo bar Texture file could not be loaded: ");
			print_error("%s\n"RESET, path);
			close_window_b(game);
		}
		game->ammo[index].addr = mlx_get_data_addr(\
			game->ammo[index].img, &game->ammo[index].bpp, \
			&game->ammo[index].line_len, &game->ammo[index].endian);
		if (!game->ammo[index].addr)
		{
			print_error(RED"Error: ammo bar texture %d address is NULL!\n"RESET, index);
			close_window_b(game);
		}
		index++;
	}
}


void	init_mlx_heart_texture_b(t_game *game)
{
	int index;
	char *path;

	index = 0;
	while (index < 12)
	{
		if (!game->heart_tex[index].path)
		{
			print_error(RED"heart Texture %d path is NULL\n"RESET, index);
			return ;
		}
		path = game->heart_tex[index].path;
		game->heart_tex[index].img = mlx_xpm_file_to_image(\
			game->mlx, path, &(game->heart_tex[index].width), \
			&(game->heart_tex[index].height));
		if (!game->heart_tex[index].img)
		{
			print_error(RED"Error: heart Texture file could not be loaded: ");
			print_error("%s\n"RESET, path);
			close_window_b(game);
		}
		game->heart_tex[index].addr = mlx_get_data_addr(\
			game->heart_tex[index].img, &game->heart_tex[index].bpp, \
			&game->heart_tex[index].line_len, &game->heart_tex[index].endian);
		if (!game->ammo[index].addr)
		{
			print_error(RED"Error: heart texture %d address is NULL!\n"RESET, index);
			close_window_b(game);
		}
		index++;
	}
}

void	init_mlx_c_ammo_texture_b(t_game *game)
{
	int index;
	char *path;

	index = 0;
	while (index < 12)
	{
		if (!game->c_ammo_tex[index].path)
		{
			print_error(RED"c_ammo Texture %d path is NULL\n"RESET, index);
			return ;
		}
		path = game->c_ammo_tex[index].path;
		game->c_ammo_tex[index].img = mlx_xpm_file_to_image(\
			game->mlx, path, &(game->c_ammo_tex[index].width), \
			&(game->c_ammo_tex[index].height));
		if (!game->c_ammo_tex[index].img)
		{
			print_error(RED"Error: c_ammo Texture file could not be loaded: ");
			print_error("%s\n"RESET, path);
			close_window_b(game);
		}
		game->c_ammo_tex[index].addr = mlx_get_data_addr(\
			game->c_ammo_tex[index].img, &game->c_ammo_tex[index].bpp, \
			&game->c_ammo_tex[index].line_len, &game->c_ammo_tex[index].endian);
		if (!game->ammo[index].addr)
		{
			print_error(RED"Error: c_ammo texture %d address is NULL!\n"RESET, index);
			close_window_b(game);
		}
		index++;
	}
}

void	init_mlx_key_texture_b(t_game *game)
{
	int index;
	char *path;

	index = 0;
	while (index < 7)
	{
		if (!game->key_tex[index].path)
		{
			print_error(RED"key Texture %d path is NULL\n"RESET, index);
			return ;
		}
		path = game->key_tex[index].path;
		game->key_tex[index].img = mlx_xpm_file_to_image(\
			game->mlx, path, &(game->key_tex[index].width), \
			&(game->key_tex[index].height));
		if (!game->key_tex[index].img)
		{
			print_error(RED"Error: key Texture file could not be loaded: ");
			print_error("%s\n"RESET, path);
			close_window_b(game);
		}
		game->key_tex[index].addr = mlx_get_data_addr(\
			game->key_tex[index].img, &game->key_tex[index].bpp, \
			&game->key_tex[index].line_len, &game->key_tex[index].endian);
		if (!game->ammo[index].addr)
		{
			print_error(RED"Error: key texture %d address is NULL!\n"RESET, index);
			close_window_b(game);
		}
		index++;
	}
}

void	init_mlx_gun_texture_b(t_game *game, int index, char *path)
{
	if (!path)
	{
		print_error(RED"GUN Texture path is NULL\n"RESET);
		return ;
	}
	game->gun[index].img = mlx_xpm_file_to_image(\
		game->mlx, path, &(game->gun[index].width), \
		&(game->gun[index].height));
	if (!game->gun[index].img)
	{
		print_error(RED"Texture file could not be loaded: ");
		print_error("%s\n"RESET, path);
		close_window_b(game);
	}
	game->gun[index].addr = mlx_get_data_addr(\
		game->gun[index].img, &game->gun[index].bpp, \
		&game->gun[index].line_len, &game->gun[index].endian);
	if (!game->gun[index].addr)
	{
		print_error(RED"Error: GUN Texture %d address is NULL!\n"RESET, index);
		close_window_b(game);
	}
}

void	init_mlx_fc_texture_b(t_game *game, int index, char *path)
{
	if (!path)
	{
		print_error(RED"Color Texture path is NULL\n"RESET);
		return ;
	}
	game->color[index].img = mlx_xpm_file_to_image(\
		game->mlx, path, &(game->color[index].width), \
		&(game->color[index].height));
	if (!game->color[index].img)
	{
		print_error(RED"Texture file could not be loaded: ");
		print_error("%s\n"RESET, path);
		close_window_b(game);
	}
	game->color[index].addr = mlx_get_data_addr(\
		game->color[index].img, &game->color[index].bpp, \
		&game->color[index].line_len, &game->color[index].endian);
	if (!game->color[index].addr)
	{
		print_error(RED"Error: color %d address is NULL!\n"RESET, index);
		close_window_b(game);
	}
}

void	load_player_b(t_game *game)
{
	if (!game->player.ini_dir)
	{
		print_error(RED"Player direction not set!\n"RESET);
		close_window_b(game);
	}
	if (ft_strncmp(game->player.ini_dir, "N", 1) == 0)
	{
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
	}
	else if (ft_strncmp(game->player.ini_dir, "S", 1) == 0)
	{
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
	}
	else if (ft_strncmp(game->player.ini_dir, "E", 1) == 0)
	{
		game->player.dir_x = 1;
		game->player.plane_y = 0.66;
	}
	else if (ft_strncmp(game->player.ini_dir, "W", 1) == 0)
	{
		game->player.dir_x = -1;
		game->player.plane_y = -0.66;
	}
}

void	set_colors_b(t_game *game, t_color *color, int index)
{
	if (color[index].mode == 1)
		color[index].hex_color = rgb_to_hex_b(color[index].r, \
			color[index].g, color[index].b);
	if (color[index].mode == 2)
		init_mlx_fc_texture_b(game, index, color[index].col_tex_str);
}

