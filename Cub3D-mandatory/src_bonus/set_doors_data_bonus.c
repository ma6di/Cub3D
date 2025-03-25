#include "cub3d_bonus.h"

void set_doors_cords(int count, t_door **door, char **map)
{
	int i = 0;
	int y = 0;
	while (map[y] && i < count)
	{
		int x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
			{
				(*door)[i].x = x;  // ✅ Use `i` as index
				(*door)[i].y = y;
				(*door)[i].door_state = 1;
				(*door)[i].transition_time = 60;
				(*door)[i].trigger = -1;
				i++;  // ✅ Increment `i`, not `count`
			}
			x++;
		}
		y++;
	}
}

int count_doors(char **map)
{
	int count;
	int y;
	int x;

	count = 0;
	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if(map[y][x] == 'D')
			{
				count++;
			}
			x++;
		}
		y++;
	}
	return count;
}

void set_doors(t_game *game)
{
	if (!game || !game->map)
		return;

	game->door_count = count_doors(game->map);
	if (game->door_count == 0)
	{
		game->door = NULL;  // ✅ No doors found, set to NULL safely
		return;
	}
	game->door = (t_door *)malloc(sizeof(t_door) * game->door_count);
	if (!game->door)  // ✅ Check for malloc failure
	{
		print_error("Error: Memory allocation for doors failed!");
		close_window_b(game);
		return;
	}

	set_doors_cords(game->door_count, &game->door, game->map);
}

void update_doors(t_game *game)
{
	long current_time;
	int i;

	current_time = get_time_of_the_day();
	for (i = 0; i < game->door_count; i++)
	{
		if(game->door[i].trigger == 1)
		{
			if (game->door[i].door_state < 5) // If the door is not fully open
			{
				// Check if 200ms have passed since the last state change
				if (current_time - game->door[i].transition_time >= 200) // 500ms delay
				{
					game->door[i].door_state++; // Increment the door state
					game->door[i].transition_time = current_time; // Reset the timer
					printf("Door state changed to %d at index %d.\n", game->door[i].door_state, i);
				}
			}
		}
		else if(game->door[i].trigger == -1)
		{
			if (game->door[i].door_state > 1) // If the door is not fully closed
			{
				// Check if 200ms have passed since the last state change
				if (current_time - game->door[i].transition_time >= 200) // 500ms delay
				{
					game->door[i].door_state--; // Decrement the door state
					game->door[i].transition_time = current_time; // Reset the timer
					printf("Door state changed to %d at index %d.\n", game->door[i].door_state, i);
				}
			}
		}
	}
}