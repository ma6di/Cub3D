
#include "cub3d_bonus.h"

int	which_door(t_game *game, double world_y, double world_x)
{
	int	map_x;
	int	map_y;
	int	i;

	i = 0;
	map_x = (int)world_x;
	map_y = (int)world_y;
	if (!game || !game->door)
		return (-1);
	while (i < game->door_count)
	{
		if (game->door[i].x == map_x && game->door[i].y == map_y)
			return (i);
		i++;
	}
	return (-1);
}

static int	check_door(t_game *game, int new_x, int new_y)
{
	int	door_index;

	if (new_y >= 0 && new_y < game->height
		&& new_x >= 0 && new_x < game->width)
	{
		if (game->map[new_y][new_x] == 'D')
		{
			door_index = which_door(game, new_y, new_x);
			if (door_index != -1)
				return (door_index);
		}
	}
	return (-1);
}

int	is_door_b(t_game *game)
{
	int	px;
	int	py;
	int	offsets[4][2];
	int	i;
	int	door_index;

	px = (int)game->player.x;
	py = (int)game->player.y;
	offsets[0][0] = 0;
	offsets[0][1] = 1;
	offsets[1][0] = 1;
	offsets[1][1] = 0;
	offsets[2][0] = 0;
	offsets[2][1] = -1;
	offsets[3][0] = -1;
	offsets[3][1] = 0;
	i = -1;
	while (++i < 4)
	{
		door_index = check_door(game, px + offsets[i][0], py + offsets[i][1]);
		if (door_index != -1)
			return (door_index);
	}
	return (-1);
}

static void	shoot_gun(t_game *game)
{
	t_sprite	*zombie;
	int			index;

	if (game->player.ammo == 0)
		return ;
	game->player.ammo -= 1;
	render_gun_shut_b(game);
	render_gun_shut_b(game);
	zombie = get_zombie_in_front(game);
	if (!zombie)
		return ;
	zombie->health -= 50;
	if (zombie->health <= 0)
	{
		index = zombie - game->sprites;
		remove_zombie(game, index);
	}
}

int	press_key_b(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window_b(game);
	else if (keycode == XK_w)
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
		shoot_gun(game);
	else if (keycode == XK_space)
	{
		if (is_door_b(game) != -1)
			game->door[is_door_b(game)].door_state = \
			!game->door[is_door_b(game)].door_state;
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
