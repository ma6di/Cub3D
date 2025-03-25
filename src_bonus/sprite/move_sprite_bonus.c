#include "cub3d_bonus.h"

static int	is_wall_or_closed_door(t_game *game, int x, int y)
{
	int	door_index;

	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == 'D')
	{
		door_index = which_door(game, y, x);
		if (door_index == -1 || game->door[door_index].door_state == 0)
			return (1);
	}
	return (0);
}

static int	is_too_close_to_wall_or_door(t_game *game, double x, double y)
{
	double	offsets[4][2];
	int		i;
	int		new_x;
	int		new_y;

	offsets[0][0] = 0;
	offsets[0][1] = 0.3;
	offsets[1][0] = 0.3;
	offsets[1][1] = 0;
	offsets[2][0] = 0;
	offsets[2][1] = -0.3;
	offsets[3][0] = -0.3;
	offsets[3][1] = 0;
	i = -1;
	while (++i < 4)
	{
		new_x = (int)(x + offsets[i][0]);
		new_y = (int)(y + offsets[i][1]);
		if (is_wall_or_closed_door(game, new_x, new_y))
			return (1);
	}
	return (0);
}

int	can_move_sprite(t_game *game, double new_x, double new_y)
{
	if (is_wall_or_closed_door(game, (int)new_x, (int)new_y))
		return (0);
	if (is_too_close_to_wall_or_door(game, new_x, new_y))
		return (0);
	return (1);
}


void move_sprites(t_game *game)
{
    int i;
    double dir_x, dir_y, length;
    double next_x, next_y;
    double move_step = 0.01;  // ✅ Small step size to avoid skipping walls
	int can_move_x;
	int can_move_y;

    for (i = 0; i < game->sprite_count; i++)
    {
        // if (!game->sprites[i].active) // ✅ Skip inactive sprites
        //     continue;

        // ✅ Calculate direction vector (normalized)
        dir_x = game->player.x - game->sprites[i].x;
        dir_y = game->player.y - game->sprites[i].y;
        length = sqrt(dir_x * dir_x + dir_y * dir_y);
        if (length == 0) // ✅ Prevent division by zero
            continue;

        dir_x /= length;
        dir_y /= length;

        // ✅ Compute new positions
        next_x = game->sprites[i].x + dir_x * move_step;
        next_y = game->sprites[i].y + dir_y * move_step;

        // ✅ Check for wall collision
		can_move_x = can_move_sprite(game, next_x, game->sprites[i].y);
		can_move_y = can_move_sprite(game, game->sprites[i].x, next_y);

        if (can_move_x && can_move_y)
        {
            // ✅ Move normally if no obstacles
            game->sprites[i].x = next_x;
            game->sprites[i].y = next_y;
        }
        else if (can_move_x)
        {
            // ✅ Slide along X-axis if Y is blocked
            game->sprites[i].x = next_x;
        }
        else if (can_move_y)
        {
            // ✅ Slide along Y-axis if X is blocked
            game->sprites[i].y = next_y;
        }
    }
}