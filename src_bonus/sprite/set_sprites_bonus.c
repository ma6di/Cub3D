
#include "cub3d_bonus.h"

int count_sprites(char **map)
{
	int count;
	int y;
	int x;

	count = 0;
	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if(map[y][x] == 'Z')
			{
				count++;
			}
			x++;
		}
		y++;
	}
	return count;
}

void set_sprites_cords(t_game *game)
{
    int x, y;
    int index = 0;
	
	game->sprite_count = count_sprites(game->map);
    game->sprites = malloc(sizeof(t_sprite) * game->sprite_count);
    if (!game->sprites)
        print_error("Error: Sprite allocation failed!");

    for (y = 0; y < game->height; y++)
    {
        for (x = 0; x < ft_strlen(game->map[y]); x++)
        {
            if (game->map[y][x] == 'Z')
            {
                game->sprites[index].x = x + 0.5; // Center in tile
                game->sprites[index].y = y + 0.5;
				game->sprites[index].distance = 0;
				game->sprites[index].visible = 0;
				game->sprites[index].health = 100;
				game->sprites[index].active = 1;
                index++;
            }
        }
    }
}