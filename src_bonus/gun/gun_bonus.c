#include "cub3d_bonus.h"

static void	draw_gun_pixel(t_game *game, int x, int y)
{
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = x;
	tex_y = y;
	color = *((int *)(game->gun[GUN].addr + \
		(tex_y * game->gun[GUN].line_len + tex_x * \
		(game->gun[GUN].bpp / 8))));
	if ((color & 0xFF000000) != 0xFF000000)
		my_mlx_pixel_put_b(game, game->gun[GUN].screen_x + x, \
			game->gun[GUN].screen_y + y, color);
}

void	draw_gun_b(t_game *game)
{
	static double	bob_phase;
	int				x;
	int				y;

	if (!game->gun[GUN].img || !game->gun[GUN].addr)
		return ((void)printf("Error: Gun texture not loaded!\n"));
	bob_phase += 0.1;
	game->gun[GUN].screen_y = SCREEN_HEIGHT - game->gun[GUN].height \
		+ (int)(fabs(sin(bob_phase)) * 4);
	y = -1;
	while (++y < game->gun[GUN].height)
	{
		x = -1;
		while (++x < game->gun[GUN].width)
			draw_gun_pixel(game, x, y);
	}
}






