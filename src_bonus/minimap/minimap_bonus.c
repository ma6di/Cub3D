#include "cub3d_bonus.h"


static void	draw_walls_b(t_game *game)
{
	t_minimap_vars	vars;

	vars.map_y = 0;
	while (vars.map_y < game->height && game->map[vars.map_y])
	{
		vars.map_x = 0;
		while (vars.map_x < game->width && game->map[vars.map_y][vars.map_x])
		{
			vars.x = vars.map_x * game->minimap.tile_size;
			vars.y = vars.map_y * game->minimap.tile_size;
			vars.tile = game->map[vars.map_y][vars.map_x];
			if (vars.tile == '1')
				draw_tile_b(game, vars.x, vars.y, 0xF00FFF);
			vars.map_x++;
		}
		vars.map_y++;
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
	int		map_y;
	int		map_x;
	int		x;
	int		y;
	char	tile;

	map_y = 0;
	while (map_y < game->height && game->map[map_y])
	{
		map_x = 0;
		while (map_x < game->width && game->map[map_y][map_x])
		{
			x = map_x * game->minimap.tile_size;
			y = map_y * game->minimap.tile_size;
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

void	minimap_b(t_game *game)
{
	draw_minimap_tiles_b(game);
	draw_player_b(game);
	draw_walls_b(game);
}
