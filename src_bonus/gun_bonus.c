
#include "cub3d_bonus.h"

void draw_gun_b(t_game *game)
{
    int x;
    int y;
    int tex_x;
    int tex_y;
    int color;
    int gun_width = game->gun[GUN].width;
    int gun_height = game->gun[GUN].height;

	static double bobbing_phase;
	int bob_offset;

	//bobbing_phase = 0;
	// ✅ Increment bobbing phase
	bobbing_phase += 0.1;
	// ✅ Use fabs(sin()) to ensure movement only goes downward
    bob_offset = (int)(fabs(sin(bobbing_phase)) * 4); // Moves 0 → 5 pixels down
    // ✅ Immediately reset back to original position
    game->gun[GUN].screen_y = SCREEN_HEIGHT - game->gun[GUN].height + bob_offset;

    if (!game->gun[GUN].img || !game->gun[GUN].addr)
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
            color = *((int *)(game->gun[GUN].addr +
                    (tex_y *  game->gun[GUN].line_len + tex_x * ( game->gun[GUN].bpp / 8))));

            // ✅ Skip transparent pixels (assuming magenta (0xFF00FF) as transparency)
			if ((color & 0xFF000000) != 0xFF000000)  // If not fully transparent
    			my_mlx_pixel_put_b(game, game->gun[GUN].screen_x + x, game->gun[GUN].screen_y + y, color);
        }
    }
}


void render_gun_shut_b(t_game *game)
{
	    int x;
    int y;
    int tex_x;
    int tex_y;
    int color;
    int width = game->gun[GUN_SHUT].width;
    int height = game->gun[GUN_SHUT].height;
	game->gun[GUN_SHUT].screen_x = (SCREEN_WIDTH / 2) - (game->gun[GUN_SHUT].width / 2);
	game->gun[GUN_SHUT].screen_y = SCREEN_HEIGHT - game->gun[GUN_SHUT].height;
	game->gun[GUN_SHUT].screen_y -= 140;
	game->gun[GUN_SHUT].screen_x -= 10;

    if (!game->gun[GUN_SHUT].img || !game->gun[GUN_SHUT].addr)
    {
        printf("Error: Gun texture not loaded properly!\n");
        return;
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            tex_x = x;
            tex_y = y;
            color = *((int *)(game->gun[GUN_SHUT].addr +
                    (tex_y *  game->gun[GUN_SHUT].line_len + tex_x * ( game->gun[GUN_SHUT].bpp / 8))));

            // ✅ Skip transparent pixels (assuming magenta (0xFF00FF) as transparency)
			if ((color & 0xFF000000) != 0xFF000000)  // If not fully transparent
    			my_mlx_pixel_put_b(game, game->gun[GUN_SHUT].screen_x + x, game->gun[GUN_SHUT].screen_y + y, color);
        }
    }
}