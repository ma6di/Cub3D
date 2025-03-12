#include "cub3d_bonus.h"

static void	init_colors(t_color *color)
{
	color[FLOOR].col_tex_str = NULL;
	color[FLOOR].mode = 0;
	color[FLOOR].r = 0;
	color[FLOOR].g = 0;
	color[FLOOR].b = 0;
	color[FLOOR].hex_color = 0;
	color[FLOOR].height = 128;
	color[FLOOR].width = 128;
	color[FLOOR].addr = NULL;
	color[FLOOR].img = NULL;
	color[CEILING].col_tex_str = NULL;
	color[CEILING].mode = 0;
	color[CEILING].r = 0;
	color[CEILING].g = 0;
	color[CEILING].b = 0;
	color[CEILING].hex_color = 0;
	color[CEILING].height = 128;
	color[CEILING].width = 128;
	color[CEILING].addr = NULL;
	color[CEILING].img = NULL;
}

void	init_minimap(t_minimap *minimap)
{
	minimap->tile_size = 7;
	minimap->offset_x = 10;
	minimap->offset_y = 10;
}

static void	init_texture(t_texture *textures, int index, int dim)
{
	textures[index].addr = NULL;
	textures[index].img = NULL;
	textures[index].path = NULL;
	if (index == DOOR)
		textures[index].door_state = 0;
	textures[index].height = dim;
	textures[index].width = dim;
}

static void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->ini_dir = NULL;
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->height = SCREEN_HEIGHT;
	game->width = SCREEN_WIDTH;
	game->map = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->map_statred = 0;
	game->file_order = 0;
	memset(game->keys, 0, sizeof(game->keys));
	init_player(&game->player);
	init_texture(game->textures, NORTH, 64);
	init_texture(game->textures, SOUTH, 64);
	init_texture(game->textures, WEST, 64);
	init_texture(game->textures, EAST, 64);
	init_texture(game->textures, DOOR, 128);
	init_colors(game->color);
	init_minimap(&game->minimap);
}
