#include "cub3d_bonus.h"


void calculate_minimap_bounds(t_game *game, int *start_x, int *end_x, int *start_y, int *end_y)
{
	int half_w = MAX_MINIMAP_WIDTH / 2;
	int half_h = MAX_MINIMAP_HEIGHT / 2;

	if (start_x)
		*start_x = (int)game->player.x - half_w;
	if (end_x)
		*end_x = (int)game->player.x + half_w;
	if (start_y)
		*start_y = (int)game->player.y - half_h;
	if (end_y)
		*end_y = (int)game->player.y + half_h;
	if (start_x && *start_x < 0)
	{
		if (end_x)
			*end_x += -*start_x;
		*start_x = 0;
	}
	if (end_x && *end_x > game->width)
	{
		if (start_x)
			*start_x -= (*end_x - game->width);
		*end_x = game->width;
	}
	if (start_y && *start_y < 0)
	{
		if (end_y)
			*end_y += -*start_y;
		*start_y = 0;
	}
	if (end_y && *end_y > game->height)
	{
		if (start_y)
			*start_y -= (*end_y - game->height);
		*end_y = game->height;
	}
}

void	draw_tile_b(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;

	j = 0;
	while (j < game->minimap.tile_size)
	{
		i = 0;
		while (i < game->minimap.tile_size)
		{
			screen_x = x + i + game->minimap.offset_x;
			screen_y = y + j + game->minimap.offset_y;
			my_mlx_pixel_put_b(game, screen_x, screen_y, color);
			i++;
		}
		j++;
	}
}

static void	draw_minimap_tiles_b(t_game *game)
{
	int		map_x, map_y;
	int		x, y;
	char	tile;
	int		start_x, end_x, start_y, end_y;

	calculate_minimap_bounds(game, &start_x, &end_x, &start_y, &end_y);
	map_y = start_y;
	while (map_y < end_y && game->map[map_y])
	{
		map_x = start_x;
		while (map_x < end_x && game->map[map_y][map_x])
		{
			x = (map_x - start_x) * game->minimap.tile_size;
			y = (map_y - start_y) * game->minimap.tile_size;
			tile = game->map[map_y][map_x];
			if (tile == '0' || ft_strchr("NWESZAKHF", tile))
				draw_tile_b(game, x, y, 0xFFFFFF);
			else if (tile == 'D')
				draw_tile_b(game, x, y, 0xFF0000);
			map_x++;
		}
		map_y++;
	}
}

static void	draw_walls_b(t_game *game)
{
	int		map_x, map_y;
	int		x, y;
	char	tile;
	int		start_x, end_x, start_y, end_y;

	calculate_minimap_bounds(game, &start_x, &end_x, &start_y, &end_y);
	map_y = start_y;
	while (map_y < end_y && game->map[map_y])
	{
		map_x = start_x;
		while (map_x < end_x && game->map[map_y][map_x])
		{
			x = (map_x - start_x) * game->minimap.tile_size;
			y = (map_y - start_y) * game->minimap.tile_size;
			tile = game->map[map_y][map_x];
			if (tile == '1')
				draw_tile_b(game, x, y, 0xF00FFF);
			map_x++;
		}
		map_y++;
	}
}

void	minimap_b(t_game *game)
{
	draw_minimap_tiles_b(game);
	draw_player_b(game);
	draw_walls_b(game);
}
