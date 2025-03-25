#include "cub3d_bonus.h"

static int	get_bob_offset(void)
{
	static double	bob_phase;

	bob_phase += 0.1;
	return ((int)(fabs(sin(bob_phase)) * 4));
}

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
	int	x;
	int	y;

	if (!game->gun[GUN].img || !game->gun[GUN].addr)
		return ((void)printf("Error: Gun texture not loaded!\n"));
	game->gun[GUN].screen_y = SCREEN_HEIGHT - game->gun[GUN].height \
		+ get_bob_offset();
	y = -1;
	while (++y < game->gun[GUN].height)
	{
		x = -1;
		while (++x < game->gun[GUN].width)
			draw_gun_pixel(game, x, y);
	}
}

static void	set_gun_shot_pos(t_game *game)
{
	game->gun[GUN_SHUT].screen_x = (SCREEN_WIDTH / 2) - \
		(game->gun[GUN_SHUT].width / 2) - 10;
	game->gun[GUN_SHUT].screen_y = SCREEN_HEIGHT - \
		game->gun[GUN_SHUT].height - 140;
}

static void	draw_shot_pixel(t_game *game, int x, int y)
{
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = x;
	tex_y = y;
	color = *((int *)(game->gun[GUN_SHUT].addr + \
		(tex_y * game->gun[GUN_SHUT].line_len + tex_x * \
		(game->gun[GUN_SHUT].bpp / 8))));
	if ((color & 0xFF000000) != 0xFF000000)
		my_mlx_pixel_put_b(game, game->gun[GUN_SHUT].screen_x + x, \
			game->gun[GUN_SHUT].screen_y + y, color);
}

void	render_gun_shut_b(t_game *game)
{
	int	x;
	int	y;

	if (!game->gun[GUN_SHUT].img || !game->gun[GUN_SHUT].addr)
		return ((void)printf("Error: Gun texture not loaded!\n"));
	set_gun_shot_pos(game);
	y = -1;
	while (++y < game->gun[GUN_SHUT].height)
	{
		x = -1;
		while (++x < game->gun[GUN_SHUT].width)
			draw_shot_pixel(game, x, y);
	}
}
