
#include "cub3d_bonus.h"

static void	loop_hook_b(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, press_key_b, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, release_key_b, game);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_rotate_b, game);
	mlx_hook(game->win, DestroyNotify, ButtonPressMask, &close_window_b, game);
	mlx_hook(game->win, 17, 0, &close_window_b, game);
	mlx_loop_hook(game->mlx, &render_b, game);
	mlx_loop(game->mlx);
}

static void	init_all_mlx_textures_b(t_game *game)
{
	init_mlx_wall_texture_b(game, NORTH, game->textures[NORTH].path);
	init_mlx_wall_texture_b(game, SOUTH, game->textures[SOUTH].path);
	init_mlx_wall_texture_b(game, WEST, game->textures[WEST].path);
	init_mlx_wall_texture_b(game, EAST, game->textures[EAST].path);
	init_mlx_wall_texture_b(game, DOOR, game->textures[DOOR].path);
	set_colors_b(game, game->color, FLOOR);
	if (game->color[CEILING].col_tex_str)
		set_colors_b(game, game->color, CEILING);
	else
		set_colors_b(game, game->color, SKY);
}

void	create_window_b(t_game *game)
{
	load_player_b(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error(RED"Error! MLX initialization failed!"RESET);
		return ;
	}
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
	{
		free(game->mlx);
		print_error(RED"Error! MLX window creation failed!"RESET);
		return ;
	}
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
	{
		print_error(RED"Error: mlx_new_image() failed!\n"RESET);
		return ;
	}
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_len, \
									&game->endian);
	init_all_mlx_textures_b(game);
	loop_hook_b(game);
}
