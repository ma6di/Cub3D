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

static void	init_minimap_b(t_minimap *minimap)
{
	minimap->tile_size = 7;
	minimap->offset_x = 10;
	minimap->offset_y = 10;
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
	player->health = 100;
	player->ammo = 6;
	player->key = 0;
}

static void	init_game_vars(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->height = SCREEN_HEIGHT;
	game->width = SCREEN_WIDTH;
	game->map = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->door = NULL;
	game->sprites = NULL;
	game->heart = NULL;
	game->c_ammo = NULL;
	game->key = NULL;
	game->map_statred = 0;
	game->file_order = 0;
	game->door_count = 0;
	game->sprite_count = 0;
	game->heart_count = 0;
	game->c_ammo_count = 0;
	game->key_count = 0;

}

void	init_game_b(t_game *game)
{
	init_game_vars(game);
	memset(game->keys, 0, sizeof(game->keys));
	init_player_b(&game->player);
	init_wall_door_textures(game);
	init_gun_b(game->gun, 150, GUN);
	init_gun_b(game->gun, 40, GUN_SHUT);
	init_health_bar_b(game->health_bar, 128, 32);
	init_ammo_b(game->ammo, 128, 32);
	init_heart_tex_b(game->heart_tex, 50);
	init_c_ammo_tex_b(game->c_ammo_tex, 32);
	init_key_tex_b(game->key_tex, 10, 27);
	init_colors_b(game->color, FLOOR, 128);
	if (game->color[CEILING].col_tex_str)
		init_colors_b(game->color, CEILING, 128);
	else
		init_colors_b(game->color, SKY, 128);
	init_minimap_b(&game->minimap);
}
