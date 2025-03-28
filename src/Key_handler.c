#include "cub3D.h"

int	press_key(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window(game);
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
