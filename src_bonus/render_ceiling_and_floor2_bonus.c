#include "cub3d_bonus.h"

int	get_cf_texture_pixel(t_color *color, int x, int y, int tex_id)
{
	char	*dst;
	int		cf_color;

	if (!color || tex_id < 0 || tex_id >= 2)
	{
		print_error(RED"Error: Invalid color ID %d\n"RESET, tex_id);
		return (-1);
	}
	if (!color[tex_id].addr)
	{
		print_error(RED"Error: color[%d].addr is NULL\n"RESET, tex_id);
		return (-1);
	}
	if (x < 0 || x >= color[tex_id].width || y < 0 || y >= color[tex_id].height)
	{
		print_error(RED"Error: Invalid coordinates for color \n"RESET);
		return (-1);
	}
	dst = color[tex_id].addr + (y * color[tex_id].line_len + \
			x * (color[tex_id].bpp / 8));
	cf_color = 0;
	ft_memcpy(&cf_color, dst, sizeof(int));
	return (cf_color);
}

void	draw_floor_tile(t_game *game, t_tile_coords *coords)
{
	int	tex_color;

	tex_color = get_cf_texture_pixel(game->color, \
	abs((int)(coords->tile_x * game->color[FLOOR].width)) % \
	game->color[FLOOR].width, abs((int)(coords->tile_y * \
	game->color[FLOOR].height)) % game->color[FLOOR].height, FLOOR);
	my_mlx_pixel_put(game, coords->x, coords->y, tex_color);
}

void	draw_floor_row(t_game *game, int y, double step_x, double step_y)
{
	int				x;
	double			floor_x;
	double			floor_y;
	t_tile_coords	coords;

	x = 0;
	floor_x = game->player.x + \
		((0.5 * SCREEN_HEIGHT) / (y - (SCREEN_HEIGHT / 2))) * \
		(game->player.dir_x - game->player.plane_x);
	floor_y = game->player.y + \
		((0.5 * SCREEN_HEIGHT) / (y - (SCREEN_HEIGHT / 2))) * \
		(game->player.dir_y - game->player.plane_y);
	while (x < SCREEN_WIDTH)
	{
		coords.x = x;
		coords.y = y;
		coords.tile_x = floor_x;
		coords.tile_y = floor_y;
		draw_floor_tile(game, &coords);
		floor_x += step_x;
		floor_y += step_y;
		x++;
	}
}

void	draw_ceiling_tile(t_game *game, t_tile_coords *coords)
{
	int	tex_color;

	tex_color = get_cf_texture_pixel(game->color, \
	abs((int)(coords->tile_x * game->color[CEILING].width)) % \
	game->color[CEILING].width, abs((int)(coords->tile_y * \
	game->color[CEILING].height)) % game->color[CEILING].height, CEILING);
	my_mlx_pixel_put(game, coords->x, coords->y, tex_color);
}

void	draw_ceiling_row(t_game *game, int y, double step_x, double step_y)
{
	int				x;
	double			ceil_x;
	double			ceil_y;
	t_tile_coords	coords;

	x = 0;
	ceil_x = game->player.x + \
		((0.5 * SCREEN_HEIGHT) / ((SCREEN_HEIGHT / 2) - y)) * \
		(game->player.dir_x - game->player.plane_x);
	ceil_y = game->player.y + \
		((0.5 * SCREEN_HEIGHT) / ((SCREEN_HEIGHT / 2) - y)) * \
		(game->player.dir_y - game->player.plane_y);
	while (x < SCREEN_WIDTH)
	{
		coords.x = x;
		coords.y = y;
		coords.tile_x = ceil_x;
		coords.tile_y = ceil_y;
		draw_ceiling_tile(game, &coords);
		ceil_x += step_x;
		ceil_y += step_y;
		x++;
	}
}
