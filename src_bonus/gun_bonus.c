
#include "cub3d_bonus.h"

void draw_gun_b(t_game *game)
{
    int x;
    int y;
    int tex_x;
    int tex_y;
    int color;
    int gun_width = game->gun.gun_width;
    int gun_height = game->gun.gun_height;

	static double bobbing_phase;
	int bob_offset;

	//bobbing_phase = 0;
	// ✅ Increment bobbing phase
	bobbing_phase += 0.1;
	// ✅ Use fabs(sin()) to ensure movement only goes downward
    bob_offset = (int)(fabs(sin(bobbing_phase)) * 4); // Moves 0 → 5 pixels down
    // ✅ Immediately reset back to original position
    game->gun.screen_y = SCREEN_HEIGHT - game->gun.gun_height + bob_offset;

    if (!game->gun.img || !game->gun.addr)
    {
        printf("Error: Gun texture not loaded properly!\n");
        return;
    }

    for (y = 0; y < gun_height; y++)
    {
        for (x = 0; x < gun_width; x++)
        {
            tex_x = x;
            tex_y = y;
            color = *((int *)(game->gun.addr +
                    (tex_y *  game->gun.line_len + tex_x * ( game->gun.bpp / 8))));

            // ✅ Skip transparent pixels (assuming magenta (0xFF00FF) as transparency)
			if ((color & 0xFF000000) != 0xFF000000)  // If not fully transparent
    			my_mlx_pixel_put_b(game, game->gun.screen_x + x, game->gun.screen_y + y, color);
        }
    }
}
