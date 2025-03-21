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
                (*door)[i].door_state = 0;
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
