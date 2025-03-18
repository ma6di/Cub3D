#include "cub3d_bonus.h"

static void	init_colors_b(t_color *color, int index, int dim)
{
	color[index].col_tex_str = NULL;
	color[index].mode = 0;
	color[index].r = 0;
	color[index].g = 0;
	color[index].b = 0;
	color[index].hex_color = 0;
	color[index].height = dim;
	color[index].width = dim;
	color[index].addr = NULL;
	color[index].img = NULL;
}

void	init_minimap_b(t_minimap *minimap)
{
	minimap->tile_size = 7;
	minimap->offset_x = 10;
	minimap->offset_y = 10;
}

static void	init_texture_b(t_texture *textures, int index, int dim)
{
	textures[index].addr = NULL;
	textures[index].img = NULL;
	textures[index].path = NULL;
	// if (index == DOOR)
	// 	textures[index].door_state = 0;
	textures[index].height = dim;
	textures[index].width = dim;
}

static void	init_player_b(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->ini_dir = NULL;
}

void	init_game_b(t_game *game)
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
	game->door_count = 0;
	memset(game->keys, 0, sizeof(game->keys));
	init_player_b(&game->player);
	init_texture_b(game->textures, NORTH, 64);
	init_texture_b(game->textures, SOUTH, 64);
	init_texture_b(game->textures, WEST, 64);
	init_texture_b(game->textures, EAST, 64);
	init_texture_b(game->textures, DOOR, 128);
	init_colors_b(game->color, FLOOR, 128);
	if (game->color[CEILING].col_tex_str)
		init_colors_b(game->color, CEILING, 128);
	else
		init_colors_b(game->color, SKY, 128);
	init_minimap_b(&game->minimap);
}
