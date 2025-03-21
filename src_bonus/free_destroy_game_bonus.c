
#include "cub3d_bonus.h"

static void	free_mlx_b(t_game *game)
{
	int	i;

	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx && game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

static void	free_mlx_gun_sprite_b(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (game->gun[i].img)
			mlx_destroy_image(game->mlx, game->gun[i].img);
		i++;
	}
	free(game->z_buffer);
}

static void	free_mlx_wall_tex_color_b(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (game->color[i].img)
			mlx_destroy_image(game->mlx, game->color[i].img);
		i++;
	}
}
static void free_textures_path_b(t_game *game)
{
	if (game->textures[NORTH].path)
		free(game->textures[NORTH].path);
	if (game->textures[SOUTH].path)
		free(game->textures[SOUTH].path);
	if (game->textures[WEST].path)
		free(game->textures[WEST].path);
	if (game->textures[EAST].path)
		free(game->textures[EAST].path);
	if (game->textures[DOOR].path)
		free(game->textures[DOOR].path);
	if (game->color[FLOOR].col_tex_str)
		free(game->color[FLOOR].col_tex_str);
	if (game->color[CEILING].col_tex_str)
		free(game->color[CEILING].col_tex_str);
	if (game->color[SKY].col_tex_str)
		free(game->color[SKY].col_tex_str);
	if (game->textures[ZOMBIE].path)
		free(game->textures[ZOMBIE].path);
	if (game->gun[GUN].path)
		free(game->gun[GUN].path);
	if (game->gun[GUN_SHUT].path)
		free(game->gun[GUN_SHUT].path);
}

int	close_window_b(t_game *game)
{
	if (game->map)
		free_two_dim_b(game->map);
	free_textures_path_b(game);
	free_mlx_wall_tex_color_b(game);
	free_mlx_gun_sprite_b(game);
	free(game->door);
	free(game->sprites);
	free_mlx_b(game);
	if ((game->player.ini_dir))
		free(game->player.ini_dir);
	free(game);
	exit(0);
}
