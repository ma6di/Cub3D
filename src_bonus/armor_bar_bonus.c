#include "cub3d_bonus.h"


void render_armor_bar_b(t_game *game)
{
	int index;
	int x;
    int y;
    int tex_x;
    int tex_y;
    int color;
	int width;
	int height;

	index = game->player.armor;
    width = game->armor[index].width;
    height = game->armor[index].height;

    if (!game->armor[index].img || !game->armor[index].addr)
    {
        printf(RED"Error: health bar texture %d not loaded properly!\n"RESET, index);
        return;
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            tex_x = x;
            tex_y = y;
            color = *((int *)(game->armor[index].addr +
                    (tex_y *  game->armor[index].line_len + tex_x * (game->armor[index].bpp / 8))));

            // ✅ Skip transparent pixels (assuming magenta (0xFF00FF) as transparency)
			if ((color & 0xFF000000) != 0xFF000000)  // If not fully transparent
    			my_mlx_pixel_put_b(game, game->armor[index].screen_x + x, game->armor[index].screen_y + y, color);
        }
    }
}
