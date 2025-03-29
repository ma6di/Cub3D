#include "cub3d_bonus.h"

void	set_player_limits(t_bounds *bounds, int map_w, int map_h)
{
	if (bounds->start_x < 0)
		bounds->start_x = 0;
	if (bounds->end_x > map_w)
		bounds->end_x = map_w;
	if (bounds->end_x - bounds->start_x < MAX_MINIMAP_WIDTH)
	{
		if (bounds->end_x - MAX_MINIMAP_WIDTH < 0)
			bounds->start_x = 0;
		else
			bounds->start_x = bounds->end_x - MAX_MINIMAP_WIDTH;
	}
	if (bounds->start_y < 0)
		bounds->start_y = 0;
	if (bounds->end_y > map_h)
		bounds->end_y = map_h;
	if (bounds->end_y - bounds->start_y < MAX_MINIMAP_HEIGHT)
	{
		if (bounds->end_y - MAX_MINIMAP_HEIGHT < 0)
			bounds->start_y = 0;
		else
			bounds->start_y = bounds->end_y - MAX_MINIMAP_HEIGHT;
	}
}

static void	set_player_bounds(t_game *game, t_bounds *bounds)
{
	int	half_w;
	int	half_h;

	half_w = MAX_MINIMAP_WIDTH / 2;
	half_h = MAX_MINIMAP_HEIGHT / 2;
	bounds->start_x = (int)game->player.x - half_w;
	bounds->end_x = (int)game->player.x + half_w;
	bounds->start_y = (int)game->player.y - half_h;
	bounds->end_y = (int)game->player.y + half_h;
	set_player_limits(bounds, game->width, game->height);
}

void	draw_player_b(t_game *game)
{
	t_bounds	bounds;
	int			px;
	int			py;

	set_player_bounds(game, &bounds);
	px = (game->player.x - bounds.start_x) * game->minimap.tile_size;
	py = (game->player.y - bounds.start_y) * game->minimap.tile_size;
	if (px >= (MAX_MINIMAP_WIDTH - 1) * game->minimap.tile_size)
		px = (MAX_MINIMAP_WIDTH - 1) * game->minimap.tile_size;
	if (py >= (MAX_MINIMAP_HEIGHT - 1) * game->minimap.tile_size)
		py = (MAX_MINIMAP_HEIGHT - 1) * game->minimap.tile_size;
	draw_view_angle_b(game, px, py);
	draw_tile_b(game, px, py, 0xc33ede);
}
