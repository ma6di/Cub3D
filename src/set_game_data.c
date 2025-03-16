
#include "cub3d.h"

void	init_mlx_wall_texture(t_game *game, int index, char *path)
{
	if (!path)
	{
		print_error(RED"Texture path is NULL\n"RESET);
		return ;
	}
	game->textures[index].img = mlx_xpm_file_to_image(\
		game->mlx, path, &(game->textures[index].width), \
		&(game->textures[index].height));
	if (!game->textures[index].img)
	{
		print_error(RED"Texture file could not be loaded: ");
		print_error("%s\n"RESET, path);
		close_window(game);
	}
	game->textures[index].addr = mlx_get_data_addr(\
		game->textures[index].img, &game->textures[index].bpp, \
		&game->textures[index].line_len, &game->textures[index].endian);
	if (!game->textures[index].addr)
	{
		print_error(RED"Error: Texture %d address is NULL!\n"RESET, index);
		close_window(game);
	}
}

void	load_player(t_game *game)
{
	if (!game->player.ini_dir)
	{
		print_error(RED"Player direction not set!\n"RESET);
		close_window(game);
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

void	set_colors(t_game *game, t_color *color, int index)
{
	color[index].hex_color = rgb_to_hex(color[index].r, \
		color[index].g, color[index].b);
}
