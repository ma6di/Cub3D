
#include "cub3d_bonus.h"

int which_door(t_game *game, double world_y, double world_x)
{
    int map_x = (int)world_x;  // ✅ Convert floating point to map grid
    int map_y = (int)world_y;

    if (!game || !game->door)  // ✅ Prevent segmentation fault
        return -1;

    for (int i = 0; i < game->door_count; i++)
    {
        if (game->door[i].x == map_x && game->door[i].y == map_y)
            return i;  // ✅ Found the door
    }

    return -1;  // No door found
}

int is_door_b(t_game *game)
{
    int px = (int)game->player.x;
    int py = (int)game->player.y;
    int door_index;

    // Check all four cardinal directions
    int offsets[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    for (int i = 0; i < 4; i++)
    {
        int new_x = px + offsets[i][0];
        int new_y = py + offsets[i][1];

        if (new_y >= 0 && new_y < game->height && new_x >= 0 && new_x < game->width)
        {
            if (game->map[new_y][new_x] == 'D')
            {
                door_index = which_door(game, new_y, new_x);
                if (door_index != -1)
                    return door_index;
            }
        }
    }

    return -1;
}


int press_key_b(int keycode, t_game *game)
{
    int door_index;

    if (keycode == XK_Escape)
        close_window_b(game);
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
	else if (keycode == XK_Control_L)
	{
        render_gun_shut_b(game);
		render_gun_shut_b(game);
		t_sprite *zombie = get_zombie_in_front(game);
		if (zombie)
		{
			zombie->health -= 50; // ✅ Reduce health by 50%
			if (zombie->health <= 0)
			{
				int index = zombie - game->sprites;  // ✅ Find index
				remove_zombie(game, index);  // ❌ Remove from array
			}
		}
    }
    else if (keycode == XK_space)
    {
        door_index = is_door_b(game);  // ✅ Avoid multiple calls
        if (door_index != -1)
            game->door[door_index].door_state = !game->door[door_index].door_state; // ✅ Toggle door state
    }
    return (0);
}


int	release_key_b(int keycode, t_game *game)
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
