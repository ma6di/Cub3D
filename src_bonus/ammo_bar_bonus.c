#include "cub3d_bonus.h"


void render_ammo_bar_b(t_game *game)
{
	int index;
	int x;
    int y;
    int tex_x;
    int tex_y;
    int color;
	int width;
	int height;

	index = game->player.ammo;
    width = game->ammo[index].width;
    height = game->ammo[index].height;

    if (!game->ammo[index].img || !game->ammo[index].addr)
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
            color = *((int *)(game->ammo[index].addr +
                    (tex_y *  game->ammo[index].line_len + tex_x * (game->ammo[index].bpp / 8))));

            // ✅ Skip transparent pixels (assuming magenta (0xFF00FF) as transparency)
			if ((color & 0xFF000000) != 0xFF000000)  // If not fully transparent
    			my_mlx_pixel_put_b(game, game->ammo[index].screen_x + x, game->ammo[index].screen_y + y, color);
        }
    }
}
