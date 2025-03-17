#include "cub3d_bonus.h"

int	get_cf_texture_pixel_b(t_color *color, int x, int y, int tex_id)
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

void	draw_floor_tile_b(t_game *game, t_tile_coords *coords)
{
	int	tex_color;

	tex_color = get_cf_texture_pixel_b(game->color, \
	abs((int)(coords->tile_x * game->color[FLOOR].width)) % \
	game->color[FLOOR].width, abs((int)(coords->tile_y * \
	game->color[FLOOR].height)) % game->color[FLOOR].height, FLOOR);
	my_mlx_pixel_put_b(game, coords->x, coords->y, tex_color);
}

void	draw_floor_row_b(t_game *game, int y, double step_x, double step_y)
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
		draw_floor_tile_b(game, &coords);
		floor_x += step_x;
		floor_y += step_y;
		x++;
	}
}

void draw_ceiling_tile_b(t_game *game, t_tile_coords *coords)
{
    int tex_x, tex_y, tex_color;
    
    // ✅ Convert player's direction to an angle
    double angle = atan2(game->player.dir_y, game->player.dir_x);
    
    // ✅ Map the rotation angle to the skybox horizontally (scale factor controls skybox width)
    double sky_rotation_factor = 0.1;  // Adjust this to control sky scrolling speed
    double sky_offset = (angle / (2 * M_PI)) * game->color[CEILING].width;

    // ✅ Compute texture coordinates
    tex_x = ((int)((coords->x / (double)SCREEN_WIDTH) * game->color[CEILING].width) + (int)sky_offset) % game->color[CEILING].width;
    if (tex_x < 0) tex_x += game->color[CEILING].width;  // Ensure positive modulo
    
    tex_y = (int)((coords->y / (double)(SCREEN_HEIGHT / 2)) * game->color[CEILING].height) % game->color[CEILING].height;

    tex_color = get_cf_texture_pixel_b(game->color, tex_x, tex_y, CEILING);
    my_mlx_pixel_put_b(game, coords->x, coords->y, tex_color);
}



void draw_ceiling_row_b(t_game *game, int y)
{
    int x;
    t_tile_coords coords;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        coords.x = x;
        coords.y = y;
        draw_ceiling_tile_b(game, &coords);
        x++;
    }
}

