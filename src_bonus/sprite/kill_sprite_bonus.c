
#include "cub3d_bonus.h"

static int	is_obstructed(t_game *game, double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;
	double	step;
	double	cur_x;
	double	cur_y;
	int		steps;
	int		i;

	dx = x2 - x1;
	dy = y2 - y1;
	step = fmax(fabs(dx), fabs(dy));
	steps = (int)step;
	dx /= step;
	dy /= step;
	cur_x = x1;
	cur_y = y1;
	i = 0;
	while (i <= steps)
	{
		if (game->map[(int)cur_y][(int)cur_x] == '1' ||
			(game->map[(int)cur_y][(int)cur_x] == 'D' &&
			game->door[which_door(game, cur_y, cur_x)].door_state == 0))
			return (1);
		cur_x += dx;
		cur_y += dy;
		i++;
	}
	return (0);
}

t_sprite	*get_zombie_in_front(t_game *game)
{
	int		i;
	double	range;
	double	min_shoot_angle;
	double	dx;
	double	dy;
	double	distance;
	double	dot;

	range = 7.0;
	min_shoot_angle = 0.3;
	i = 0;
	while (i < game->sprite_count)
	{
		if (!game->sprites[i].active)
		{
			i++;
			continue ;
		}
		dx = game->sprites[i].x - game->player.x;
		dy = game->sprites[i].y - game->player.y;
		distance = sqrtf(dx * dx + dy * dy);
		if (distance < range)
		{
			dot = (dx * game->player.dir_x + dy * game->player.dir_y) / distance;
			if (dot > min_shoot_angle && !is_obstructed(game,
					game->player.x, game->player.y,
					game->sprites[i].x, game->sprites[i].y))
				return (&game->sprites[i]);
		}
		i++;
	}
	return (NULL);
}



void remove_zombie(t_game *game, int index)
{
    if (index < 0 || index >= game->sprite_count)
        return;

    // ✅ Shift all zombies after the index forward
    for (int i = index; i < game->sprite_count - 1; i++)
       		game->sprites[i] = game->sprites[i + 1];

    game->sprite_count--;  // ✅ Reduce total count
}