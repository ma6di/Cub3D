
#include "cub3d_bonus.h"

void sort_sprites(t_game *game)
{
    int i, j;
    t_sprite temp;

    for (i = 0; i < game->sprite_count - 1; i++)
    {
        for (j = i + 1; j < game->sprite_count; j++)
        {
            if (game->sprites[i].distance < game->sprites[j].distance)
            {
                temp = game->sprites[i];
                game->sprites[i] = game->sprites[j];
                game->sprites[j] = temp;
            }
        }
    }
}

void render_sprites(t_game *game, t_sprite *sprite)
{
    int x, y;
    int tex_x, tex_y, color;
    double sprite_x, sprite_y, inv_det;
    double transform_x, transform_y;
    int sprite_screen_x, sprite_height, sprite_width;
    int draw_start_x, draw_start_y, draw_end_x, draw_end_y;

    if (!game->textures[ZOMBIE].addr)
    {
        printf("Error: Zombie texture is not loaded!\n");
        return;
    }

    // ✅ Update sprite distance (for sorting)
    sprite->distance = pow(game->player.x - sprite->x, 2) +
                       pow(game->player.y - sprite->y, 2);

    sprite_x = sprite->x - game->player.x;
    sprite_y = sprite->y - game->player.y;

    // ✅ Transform sprite to camera space
    inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - game->player.dir_x * game->player.plane_y);
    transform_x = inv_det * (game->player.dir_y * sprite_x - game->player.dir_x * sprite_y);
    transform_y = inv_det * (-game->player.plane_y * sprite_x + game->player.plane_x * sprite_y);

    // ✅ If behind player, don't render
    if (transform_y <= 0.01)
        return;

    // ✅ Screen X position
    sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + transform_x / transform_y));

    // ✅ Scale sprite size based on distance
    sprite_height = abs((int)(SCREEN_HEIGHT / transform_y)) / 2;
    sprite_width = abs((int)(SCREEN_WIDTH / transform_y)) / 2;

    // ✅ Calculate draw start & end positions
	draw_start_y = SCREEN_HEIGHT / 2 + 10;
	draw_end_y = draw_start_y + sprite_height;
	draw_start_x = sprite_screen_x - sprite_width / 2;
	draw_end_x = sprite_screen_x + sprite_width / 2;

    // ✅ Bounds check to prevent sprites from disappearing at screen edges
    if (draw_end_x >= SCREEN_WIDTH) draw_end_x = SCREEN_WIDTH - 1;
    if (draw_start_y < 0) draw_start_y = 0;
    if (draw_end_y >= SCREEN_HEIGHT) draw_end_y = SCREEN_HEIGHT - 1;

    // ✅ Render sprite pixels
    for (x = draw_start_x; x < draw_end_x; x++)
    {
        if (x < 0 || x >= SCREEN_WIDTH)  
            continue;

        tex_x = (x - draw_start_x) * game->textures[ZOMBIE].width / sprite_width;

        if (tex_x < 0 || tex_x >= game->textures[ZOMBIE].width)
            continue;

        // ✅ Ensure sprite isn't behind a wall
        if (transform_y > game->z_buffer[x])  
            continue;

        for (y = draw_start_y; y < draw_end_y; y++)
        {
            tex_y = (y - draw_start_y) * game->textures[ZOMBIE].height / sprite_height;

            if (tex_y < 0 || tex_y >= game->textures[ZOMBIE].height)
                continue;

            // ✅ Get color from texture
            char *pixel = game->textures[ZOMBIE].addr +
                          (tex_y * game->textures[ZOMBIE].line_len) +
                          (tex_x * (game->textures[ZOMBIE].bpp / 8));

            color = 0;
            ft_memcpy(&color, pixel, sizeof(int));

            // ✅ Apply transparency check (assuming 0xFF00FF is the transparent color)
			if ((color & 0x00FFFFFF) != 0)  // ✅ Skip fully transparent pixels
                my_mlx_pixel_put_b(game, x, y, color);
        }
    }
}








