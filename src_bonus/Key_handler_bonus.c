
#include "cub3d_bonus.h"

int	is_door(t_game *game)
{
	int	px;
	int	py;

	px = (int)game->player.x;
	py = (int)game->player.y;
	if (py + 1 < game->height && game->map[py + 1][px] == 'D')
		return (1);
	if (px + 1 < game->width && game->map[py][px + 1] == 'D')
		return (1);
	if (py - 1 >= 0 && game->map[py - 1][px] == 'D')
		return (1);
	if (px - 1 >= 0 && game->map[py][px - 1] == 'D')
		return (1);
	if (py - 1 >= 0 && px - 1 >= 0 && game->map[py - 1][px - 1] == 'D')
		return (1);
	if (py + 1 < game->height && px + 1 < game->width && \
		game->map[py + 1][px + 1] == 'D')
		return (1);
	return (0);
}

int	press_key(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		close_window(game);
		game->win = NULL;
		exit(0);
	}
	if (keycode == XK_w)
		game->keys[KEY_W] = 1;
	else if (keycode == XK_s)
		game->keys[KEY_S] = 1;
	else if (keycode == XK_a)
		game->keys[KEY_A] = 1;
	else if (keycode == XK_d)
		game->keys[KEY_D] = 1;
	else if (keycode == XK_Left)
		game->keys[KEY_LEFT] = 1;
	else if (keycode == XK_Right)
		game->keys[KEY_RIGHT] = 1;
	else if (keycode == XK_space && is_door(game) && \
		game->textures[DOOR].door_state == 1)
		game->textures[DOOR].door_state = 0;
	else if (keycode == XK_space && is_door(game) && \
				game->textures[DOOR].door_state == 0)
		game->textures[DOOR].door_state = 1;
	return (0);
}

int	release_key(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys[KEY_W] = 0;
	else if (keycode == XK_s)
		game->keys[KEY_S] = 0;
	else if (keycode == XK_a)
		game->keys[KEY_A] = 0;
	else if (keycode == XK_d)
		game->keys[KEY_D] = 0;
	else if (keycode == XK_Left)
		game->keys[KEY_LEFT] = 0;
	else if (keycode == XK_Right)
		game->keys[KEY_RIGHT] = 0;
	return (0);
}
