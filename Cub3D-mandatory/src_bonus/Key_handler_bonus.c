#include "cub3d_bonus.h"

int	which_door(t_game *game, double world_y, double world_x)
{
	int	map_x;
	int	map_y;
	int	i;

	if (!game || !game->door)
		return (-1);
	map_x = (int)world_x;
	map_y = (int)world_y;
	i = 0;
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

static int	is_zombie_inside_door(t_game *game, int index)
{
	int	i;
	int	z_x;
	int	z_y;

	i = 0;
	while (i < game->sprite_count)
	{
		if (!game->sprites[i].active)
		{
			i++;
			continue ;
		}
		z_x = (int)game->sprites[i].x;
		z_y = (int)game->sprites[i].y;
		if (z_x == game->door[index].x && \
			z_y == game->door[index].y)
			return (1);
		i++;
	}
	return (0);
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

// static void change_door_state(t_game *game, int index)
// {
//     printf("Changing state of door at index %d.\n", index);

//     // Continue transitioning until the door reaches state 5
//     while (game->door[index].transition_time > 0)
//     {
//         // Calculate the intermediate state based on the remaining transition time
//         int progress = 10000 - game->door[index].transition_time; // Progress from 0 to 1000
//         game->door[index].door_state = 1 + ((progress * 4) / 10000); // Map progress to states 1 to 5

//         printf("Door state during transition: %d (progress: %d).\n", game->door[index].door_state, progress);

//         game->door[index].transition_time--; // Decrease the timer
//     }
// 	game->door[index].door_state = 5;
//     // Reset the transition time for the next interaction
//     game->door[index].transition_time = 10000;
//     printf("Door fully opened. State: %d.\n", game->door[index].door_state);
// }

// static void change_door_state(t_game *game, int index)
// {
//     printf("Changing state of door at index %d.\n", index);

//     // Continue transitioning until the door reaches state 5
//     while (game->door[index].door_state < 6)
//     {
// 		game->door[index].transition_time --;
// 		if(game->door[index].transition_time == 0)
// 		{
//         	game->door[index].door_state ++;; // Map progress to states 1 to 5
// 			game->door[index].transition_time = 6000;
// 		}
//     }
// 	game->door[index].door_state = 5;
// }
long get_time_of_the_day(void)
{
    struct timeval tv;

    // Get the current time
    if (gettimeofday(&tv, NULL) == -1)
    {
        perror("gettimeofday failed");
        return -1;
    }

    // Return the time in milliseconds
    return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
}

static void change_door_state(t_game *game, int index)
{
	game->door[index].trigger *= -1;
	game->door[index].transition_time = get_time_of_the_day(); // Record the starting time
    printf("Starting door transition at index %d.\n", index);
}
int is_final_door(t_game *game)
{
	if(game->map[(int)game->player.y + 1][(int)game->player.x + 1] == 'F')
		return 1;
	if(game->map[(int)game->player.y][(int)game->player.x + 1] == 'F')
		return 1;
	if(game->map[(int)game->player.y + 1][(int)game->player.x] == 'F')
		return 1;
	if(game->map[(int)game->player.y - 1][(int)game->player.x - 1] == 'F')
		return 1;
	if(game->map[(int)game->player.y][(int)game->player.x - 1] == 'F')
		return 1;
	if(game->map[(int)game->player.y - 1][(int)game->player.x] == 'F')
		return 1;
	return 0;

}
int	press_key_b(int keycode, t_game *game)
{
	int	index;

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
		index = is_door_b(game);
		if (index != -1 && !is_zombie_inside_door(game, index))
			change_door_state(game, index);
		if(is_final_door(game) && game->player.key > 0)
		{
			printf("VICTORY\n");
			printf("VICTORY\n");
			printf("VICTORY\n");
			close_window_b(game);
		}
		
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
