#include "cub3d_bonus.h"

void	check_collect_key(t_game *game)
{
	int	i;
	int	key_x;
	int	key_y;

	i = -1;
	while (++i < game->key_count)
	{
		if (!game->key[i].active)
			continue ;
		key_x = (int)game->key[i].x;
		key_y = (int)game->key[i].y;
		if ((int)game->player.x == key_x && (int)game->player.y == key_y)
		{
			game->player.key += 1;
			printf("Player total keys: %d\n", game->player.key);
			game->key[i].active = 0;
		}
	}
}

int	calculate_transform_key(t_game *game, t_key *key, \
	double *transform_x, double *transform_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = key->x - game->player.x;
	sprite_y = key->y - game->player.y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	*transform_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	*transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
	if (*transform_y <= 0)
		return (0);
	return (1);
}

void	calculate_draw_positions_key(t_game *game, double transform_x, \
	double transform_y, t_draw *draw)
{
	double	scale;

	scale = 0.15;
	draw->screen_x = (int)((SCREEN_WIDTH / 2)
			* (1 + transform_x / transform_y));
	draw->height = abs((int)(SCREEN_HEIGHT / transform_y)) * scale;
	draw->width = abs((int)(SCREEN_WIDTH / transform_y)) * scale;
	draw->start_y = SCREEN_HEIGHT / 2 + 20;
	draw->end_y = draw->start_y + draw->height;
	draw->start_x = draw->screen_x - draw->width / 2;
	draw->end_x = draw->screen_x + draw->width / 2;
}
