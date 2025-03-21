
#include "cub3d.h"

static void	free_mlx(t_game *game)
{
	int	i;

	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->mlx && game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	close_window(t_game *game)
{
	free_mlx(game);
	if (game->map)
		free_two_dim(game->map);
	if (game->textures[NORTH].path)
		free(game->textures[NORTH].path);
	if (game->textures[SOUTH].path)
		free(game->textures[SOUTH].path);
	if (game->textures[WEST].path)
		free(game->textures[WEST].path);
	if (game->textures[EAST].path)
		free(game->textures[EAST].path);
	if (game->color[FLOOR].col_tex_str)
		free(game->color[FLOOR].col_tex_str);
	if (game->color[CEILING].col_tex_str)
		free(game->color[CEILING].col_tex_str);
	if ((game->player.ini_dir))
		free(game->player.ini_dir);
	free(game);
	exit(0);
}
