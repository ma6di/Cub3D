#include "cub3d_bonus.h"

void	draw_tile_b(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;
	int	tile_size;

	tile_size = game->minimap.tile_size;
	j = 0;
	while (j < tile_size)
	{
		i = 0;
		while (i < tile_size)
		{
			screen_x = x + i + game->minimap.offset_x;
			screen_y = y + j + game->minimap.offset_y;
			my_mlx_pixel_put_b(game, screen_x, screen_y, color);
			i++;
		}
		j++;
	}
}

static void	draw_minimap_tiles_b(t_game *game, t_bounds *bounds)
{
	int		map_x;
	int		map_y;
	int		x;
	int		y;
	char	tile;

	map_y = bounds->start_y;
	while (map_y < bounds->end_y && game->map[map_y])
	{
		map_x = bounds->start_x;
		while (map_x < bounds->end_x && game->map[map_y][map_x])
		{
			x = (map_x - bounds->start_x) * game->minimap.tile_size;
			y = (map_y - bounds->start_y) * game->minimap.tile_size;
			tile = game->map[map_y][map_x];
			if (tile == '0' || ft_strchr("NWESZAKHF", tile))
				draw_tile_b(game, x, y, 0xbfbbb8);
			else if (tile == 'D')
				draw_tile_b(game, x, y, 0x0b73db);
			map_x++;
		}
		map_y++;
	}
}

static void	draw_walls_b(t_game *game, t_bounds *bounds)
{
	int		map_x;
	int		map_y;
	int		x;
	int		y;

	map_y = bounds->start_y;
	while (map_y < bounds->end_y && game->map[map_y])
	{
		map_x = bounds->start_x;
		while (map_x < bounds->end_x && game->map[map_y][map_x])
		{
			x = (map_x - bounds->start_x) * game->minimap.tile_size;
			y = (map_y - bounds->start_y) * game->minimap.tile_size;
			if (game->map[map_y][map_x] == '1')
				draw_tile_b(game, x, y, 0x873b01);
			map_x++;
		}
		map_y++;
	}
}

void	set_minimap_bounds(t_game *game, t_bounds *bounds)
{
	int	half_w;
	int	half_h;

	half_w = MAX_MINIMAP_WIDTH / 2;
	half_h = MAX_MINIMAP_HEIGHT / 2;
	bounds->start_x = (int)game->player.x - half_w;
	bounds->end_x = (int)game->player.x + half_w;
	bounds->start_y = (int)game->player.y - half_h;
	bounds->end_y = (int)game->player.y + half_h;
	set_minimap_limits(bounds, game->width, game->height);
}

void	minimap_b(t_game *game)
{
	t_bounds	bounds;

	set_minimap_bounds(game, &bounds);
	draw_minimap_tiles_b(game, &bounds);
	draw_player_b(game);
	draw_walls_b(game, &bounds);
}
