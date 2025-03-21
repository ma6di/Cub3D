
#include "cub3d_bonus.h"

int count_key(char **map)
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
			if(map[y][x] == 'K')
			{
				count++;
			}
			x++;
		}
		y++;
	}
	return count;
}

void set_key_cords(t_game *game)
{
    int x, y;
    int index = 0;
	
	game->key_count = count_key(game->map);
    game->key = malloc(sizeof(t_key) * game->key_count);
    if (!game->key)
        print_error("Error: Sprite allocation failed!");

    for (y = 0; y < game->height; y++)
    {
        for (x = 0; x < ft_strlen(game->map[y]); x++)
        {
            if (game->map[y][x] == 'K')
            {
                game->key[index].x = x + 0.5; // Center in tile
                game->key[index].y = y + 0.5;
				game->key[index].distance = 0;
				game->key[index].visible = 0;
				game->key[index].active = 1;
				game->key[index].animation_index = 0; // Start at frame 0
                game->key[index].animation_timer = 0;
                index++;
            }
        }
    }
}

void sort_keys(t_game *game)
{
    int i, j;
    t_key temp;

    for (i = 0; i < game->key_count - 1; i++)
    {
        for (j = i + 1; j < game->key_count; j++)
        {
            if (game->key[i].distance < game->key[j].distance)
            {
                temp = game->key[i];
                game->key[i] = game->key[j];
                game->key[j] = temp;
            }
        }
    }
}

void render_key(t_game *game)
{
    int i, x, y;
    int tex_x, tex_y, color;
    double sprite_x, sprite_y, inv_det;
    double transform_x, transform_y;
    int sprite_screen_x, sprite_height, sprite_width, draw_start_x, draw_start_y, draw_end_x, draw_end_y;

    if (!game->key_tex[0].addr)
    {
        printf("Error: key textures are not loaded!\n");
        return;
    }

    // ✅ Update animation every few frames
    for (i = 0; i < game->key_count; i++)
    {
        if (!game->key[i].active)  // Skip collected hearts
            continue;

        // 🔄 Increment animation timer
        game->key[i].animation_timer++;

        // 🔄 Change frame every 10 game ticks (adjust as needed)
        if (game->key[i].animation_timer >= 10)
        {
            game->key[i].animation_index = (game->key[i].animation_index + 1) % 7;
            game->key[i].animation_timer = 0;  // Reset timer
        }

        // ✅ Update distance for rendering order
        game->key[i].distance = pow(game->player.x - game->key[i].x, 2) +
                                  pow(game->player.y - game->key[i].y, 2);
    }

    sort_keys(game);  // ✅ Sort keys by distance (farther ones first)

    for (i = 0; i < game->key_count; i++)
    {
        if (!game->key[i].active) // ✅ Skip collected keys
            continue;

        sprite_x = game->key[i].x - game->player.x;
        sprite_y = game->key[i].y - game->player.y;

        inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - game->player.dir_x * game->player.plane_y);
        transform_x = inv_det * (game->player.dir_y * sprite_x - game->player.dir_x * sprite_y);
        transform_y = inv_det * (-game->player.plane_y * sprite_x + game->player.plane_x * sprite_y);

        if (transform_y <= 0)  // ✅ Skip keys behind the player
            continue;

// Adjust this scaling factor to control the key size
		double scale = 0.15; // 50% smaller

		sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + transform_x / transform_y));

		// Scale the height and width to make the key smaller
		sprite_height = abs((int)(SCREEN_HEIGHT / transform_y)) * scale;
		sprite_width = abs((int)(SCREEN_WIDTH / transform_y)) * scale;

        draw_start_y = SCREEN_HEIGHT / 2 + 20;
		draw_end_y = draw_start_y + sprite_height;
		draw_start_x = sprite_screen_x - sprite_width / 2;
		draw_end_x = sprite_screen_x + sprite_width / 2;


        for (x = draw_start_x; x < draw_end_x; x++)
        {
            if (x < 0 || x >= SCREEN_WIDTH)  // ✅ Skip out-of-bounds columns
                continue;

            tex_x = (x - draw_start_x) * game->key_tex[0].width / sprite_width;
            if (tex_x < 0 || tex_x >= game->key_tex[0].width)
                continue;

            if (transform_y > game->z_buffer[x])  // ✅ Skip if behind a wall
                continue;

            for (y = draw_start_y; y < draw_end_y; y++)
            {
                tex_y = (y - draw_start_y) * game->key_tex[0].height / sprite_height;
                if (tex_y < 0 || tex_y >= game->key_tex[0].height)
                    continue;

                // ✅ Use the current animated frame
                int frame = game->key[i].animation_index;
                char *pixel = game->key_tex[frame].addr +
                              (tex_y * game->key_tex[frame].line_len) +
                              (tex_x * (game->key_tex[frame].bpp / 8));

                color = 0;
                ft_memcpy(&color, pixel, sizeof(int));

                if ((color & 0x00FFFFFF) != 0)  // ✅ Skip fully transparent pixels
                    my_mlx_pixel_put_b(game, x, y, color);
            }
        }
    }
}



void check_collect_key(t_game *game)
{
    for (int i = 0; i < game->key_count; i++)
    {
        if (!game->key[i].active) // ✅ Skip inactive keys
            continue;

        int key_x = (int)game->key[i].x;
        int key_y = (int)game->key[i].y;
        int player_x = (int)game->player.x;
        int player_y = (int)game->player.y;

        if (player_x == key_x && player_y == key_y)
        {
            game->player.key += 1;  // ✅ Heal player  
			printf("player total keys: %d\n",  game->player.key);
            game->key[i].active = 0; // ❌ Remove c_ammo from rendering
        }
    }
}
