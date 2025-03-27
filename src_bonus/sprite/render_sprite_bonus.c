#include "cub3d_bonus.h"

static void	calculate_sprite_dims(t_sprite_draw *draw)
{
	draw->screen_x = (int)((SCREEN_WIDTH / 2) \
					* (1 + draw->transform_x / draw->transform_y));
	draw->height = abs((int)(SCREEN_HEIGHT / draw->transform_y)) / 2;
	draw->width = abs((int)(SCREEN_WIDTH / draw->transform_y)) / 2;
	draw->start_y = SCREEN_HEIGHT / 2 + 10;
	draw->end_y = draw->start_y + draw->height;
	draw->start_x = draw->screen_x - draw->width / 2;
	draw->end_x = draw->screen_x + draw->width / 2;
}

static int	get_pixel_color(t_game *game, int tex_x, int tex_y)
{
	char	*pixel;
	int		color;

	pixel = game->textures[ZOMBIE].addr + \
			(tex_y * game->textures[ZOMBIE].line_len) \
			+ (tex_x * (game->textures[ZOMBIE].bpp / 8));
	ft_memcpy(&color, pixel, sizeof(int));
	return (color);
}

static void	draw_sprite_column(t_game *game, t_sprite_draw *draw, int x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;

	tex_x = get_tex_x(game, draw, x);
	y = draw->start_y;
	while (y < draw->end_y)
	{
		tex_y = get_tex_y(game, draw, y);
		color = get_pixel_color(game, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put_b(game, x, y, color);
		y++;
	}
}

static void	render_sprite_pixels(t_game *game, t_sprite_draw *draw)
{
	int	x;

	x = draw->start_x;
	while (x < draw->end_x)
	{
		if (x >= 0 && x < SCREEN_WIDTH && \
				draw->transform_y <= game->z_buffer[x])
			draw_sprite_column(game, draw, x);
		x++;
	}
}

void	render_sprites(t_game *game, t_sprite *sprite)
{
	t_sprite_draw	draw;

	if (!transform_sprite(game, sprite, &draw))
		return ;
	calculate_sprite_dims(&draw);
	render_sprite_pixels(game, &draw);
}
