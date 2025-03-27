#include "cub3d_bonus.h"

static void	init_texture_b(t_texture *textures, int index, int dim)
{
	textures[index].addr = NULL;
	textures[index].img = NULL;
	textures[index].path = NULL;
	textures[index].height = dim;
	textures[index].width = dim;
}

void	init_wall_door_textures(t_game *game)
{
	init_texture_b(game->textures, NORTH, 64);
	init_texture_b(game->textures, SOUTH, 64);
	init_texture_b(game->textures, WEST, 64);
	init_texture_b(game->textures, EAST, 64);
	init_texture_b(game->textures, DOOR_1, 128);
	init_texture_b(game->textures, DOOR_2, 128);
	init_texture_b(game->textures, DOOR_3, 128);
	init_texture_b(game->textures, DOOR_4, 128);
	init_texture_b(game->textures, DOOR_5, 128);
	init_texture_b(game->textures, FINAL_DOOR, 128);
	init_texture_b(game->textures, ZOMBIE_0, 220);
	init_texture_b(game->textures, ZOMBIE_1, 220);
	init_texture_b(game->textures, ZOMBIE_2, 220);
}
