#include "../../include/cub3d_bonus.h"

int	close_window_b(t_game *game)
{
	if (game->map)
		free_two_dim_b(game->map);
	free_textures_path_b(game);
	free_mlx_b(game);
	if (game->door)
		free(game->door);
	if (game->sprites)
		free(game->sprites);
	if (game->c_ammo)
		free(game->c_ammo);
	if (game->heart)
		free(game->heart);
	if (game->key)
		free(game->key);
	if ((game->player.ini_dir))
		free(game->player.ini_dir);
	free(game);
	exit(0);
}
