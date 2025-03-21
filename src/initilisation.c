#include "cub3d.h"

static void	init_colors(t_color *color)
{
	color[FLOOR].col_tex_str = NULL;
	color[FLOOR].r = 0;
	color[FLOOR].g = 0;
	color[FLOOR].b = 0;
	color[FLOOR].hex_color = 0;
	color[CEILING].col_tex_str = NULL;
	color[CEILING].r = 0;
	color[CEILING].g = 0;
	color[CEILING].b = 0;
	color[CEILING].hex_color = 0;
}

static void	init_texture(t_texture *textures, int index, int dim)
{
	textures[index].addr = NULL;
	textures[index].img = NULL;
	textures[index].path = NULL;
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
	init_colors(game->color);
}
