
#include "cub3D.h"


int is_door(t_game *game)
{
	int px = (int)game->player.x;
	int py = (int)game->player.y;
	
	if (py + 1 < game->height && game->map[py + 1][px] == 'D')
		return 1;
	if (px + 1 < game->width && game->map[py][px + 1] == 'D')
		return 1;
	if (py - 1 >= 0 && game->map[py - 1][px] == 'D')
		return 1;
	if (px - 1 >= 0 && game->map[py][px - 1] == 'D')
		return 1;
	if (py - 1 >= 0 && px - 1 >= 0 && game->map[py - 1][px - 1] == 'D')
		return 1;
	if (py + 1 < game->height && px + 1 < game->width && game->map[py + 1][px + 1] == 'D')
		return 1;
	
	return 0;	
}

int press_key(int keycode, t_game *game)
{
    // 🔴 Exit Game
    if (keycode == XK_Escape)
    {
        close_window(game);
		game->win = NULL;
        exit(0);
    }

    // 🟢 Movement Controls (WASD / Arrow Keys)
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

int release_key(int keycode, t_game *game)
{
    // 🟢 Movement Controls (WASD / Arrow Keys)
    if (keycode == XK_w)
        game->keys[KEY_W] = 0;
    else if (keycode == XK_s)
		game->keys[KEY_S] = 0;
    else if (keycode == XK_a)
		game->keys[KEY_A] = 0;
    else if (keycode == XK_d)
		game->keys[KEY_D] = 0;
    // 🔄 Rotation Controls (Left/Right Arrows)
    else if (keycode == XK_Left)
		game->keys[KEY_LEFT] = 0;
    else if (keycode == XK_Right)
		game->keys[KEY_RIGHT] = 0;
    return (0);
}


