#include "cub3D.h"

void	draw_ceiling_pixel(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT / 2)
		{
			my_mlx_pixel_put(game, x, y, game->color[CEILING].hex_color);
			y++;
		}
		x++;
	}
}

void	draw_floor_pixel(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = SCREEN_HEIGHT / 2;
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(game, x, y, game->color[FLOOR].hex_color);
			y++;
		}
		x++;
	}
}


void	draw_floor_and_ceiling(t_game *game, int index)
{
	(void)(index);
	draw_ceiling_pixel(game);
	draw_floor_pixel(game);
}