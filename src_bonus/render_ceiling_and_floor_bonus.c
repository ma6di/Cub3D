#include "cub3d_bonus.h"


void	draw_ceiling_pixel_b(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT / 2)
		{
			my_mlx_pixel_put_b(game, x, y, game->color[CEILING].hex_color);
			y++;
		}
		x++;
	}
}

void	draw_floor_pixel_b(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = SCREEN_HEIGHT / 2;
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put_b(game, x, y, game->color[FLOOR].hex_color);
			y++;
		}
		x++;
	}
}

void	draw_floor_texture_b(t_game *game)
{
	int		y;
	double	row_distance;
	double	step_x;
	double	step_y;

	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		row_distance = (0.5 * SCREEN_HEIGHT) / (y - (SCREEN_HEIGHT / 2));
		step_x = row_distance * (game->player.dir_x + game->player.plane_x - \
			(game->player.dir_x - game->player.plane_x)) / SCREEN_WIDTH;
		step_y = row_distance * (game->player.dir_y + game->player.plane_y - \
			(game->player.dir_y - game->player.plane_y)) / SCREEN_WIDTH;
		draw_floor_row_b(game, y, step_x, step_y);
		y++;
	}
}

void	draw_ceiling_texture_b(t_game *game)
{
	int		y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		draw_ceiling_row_b(game, y);
		y++;
	}
}

void	draw_floor_and_ceiling_b(t_game *game, int index)
{
	if (game->color[index].mode == 1)
	{
		if (index == CEILING)
			draw_ceiling_pixel_b(game);
		else if (index == FLOOR)
			draw_floor_pixel_b(game);
	}
	else
	{
		if (index == CEILING)
			draw_ceiling_texture_b(game);
		else if (index == FLOOR)
			draw_floor_texture_b(game);
	}
}
