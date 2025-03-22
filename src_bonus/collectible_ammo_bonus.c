
#include "cub3d_bonus.h"

int count_c_ammo(char **map)
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
			if(map[y][x] == 'A')
			{
				count++;
			}
			x++;
		}
		y++;
	}
	return count;
}

void set_c_ammo_cords(t_game *game)
{
    int x, y;
    int index = 0;
	
	game->c_ammo_count = count_c_ammo(game->map);
    game->c_ammo = malloc(sizeof(t_c_ammo) * game->c_ammo_count);
    if (!game->c_ammo)
        print_error("Error: Sprite allocation failed!");

    for (y = 0; y < game->height; y++)
    {
        for (x = 0; x < ft_strlen(game->map[y]); x++)
        {
            if (game->map[y][x] == 'A')
            {
                game->c_ammo[index].x = x + 0.5; // Center in tile
                game->c_ammo[index].y = y + 0.5;
				game->c_ammo[index].distance = 0;
				game->c_ammo[index].visible = 0;
				game->c_ammo[index].active = 1;
				game->c_ammo[index].animation_index = 0; // Start at frame 0
                game->c_ammo[index].animation_timer = 0;
                index++;
            }
        }
    }
}

void sort_c_ammos(t_game *game)
{
    int i, j;
    t_c_ammo temp;

    for (i = 0; i < game->c_ammo_count - 1; i++)
    {
        for (j = i + 1; j < game->c_ammo_count; j++)
        {
            if (game->c_ammo[i].distance < game->c_ammo[j].distance)
            {
                temp = game->c_ammo[i];
                game->c_ammo[i] = game->c_ammo[j];
                game->c_ammo[j] = temp;
            }
        }
    }
}

void render_c_ammo(t_game *game, t_c_ammo *c_ammo)
{
    int i, x, y;
    int tex_x, tex_y, color;
    double sprite_x, sprite_y, inv_det;
    double transform_x, transform_y;
    int sprite_screen_x, sprite_height, sprite_width, draw_start_x, draw_start_y, draw_end_x, draw_end_y;

    if (!game->c_ammo_tex[0].addr)
    {
        printf("Error: c_ammo textures are not loaded!\n");
        return;
    }

    // ✅ Update animation every few frames
  
        if (!c_ammo->active)  // Skip collected hearts
            return;

        // 🔄 Increment animation timer
        c_ammo->animation_timer++;

        // 🔄 Change frame every 10 game ticks (adjust as needed)
        if (c_ammo->animation_timer >= 10)
        {
            c_ammo->animation_index = (c_ammo->animation_index + 1) % 12;
            c_ammo->animation_timer = 0;  // Reset timer
        }

        // ✅ Update distance for rendering order
        c_ammo->distance = pow(game->player.x - c_ammo->x, 2) +
                                  pow(game->player.y - c_ammo->y, 2);


    // sort_c_ammos(game);  // ✅ Sort c_ammos by distance (farther ones first)

        if (!c_ammo->active) // ✅ Skip collected c_ammos
            return;

        sprite_x = c_ammo->x - game->player.x;
        sprite_y = c_ammo->y - game->player.y;

        inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - game->player.dir_x * game->player.plane_y);
        transform_x = inv_det * (game->player.dir_y * sprite_x - game->player.dir_x * sprite_y);
        transform_y = inv_det * (-game->player.plane_y * sprite_x + game->player.plane_x * sprite_y);

        if (transform_y <= 0)  // ✅ Skip c_ammos behind the player
            return;

// Adjust this scaling factor to control the c_ammo size
		double scale = 0.15; // 50% smaller

		sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + transform_x / transform_y));

		// Scale the height and width to make the c_ammo smaller
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

            tex_x = (x - draw_start_x) * game->c_ammo_tex[0].width / sprite_width;
            if (tex_x < 0 || tex_x >= game->c_ammo_tex[0].width)
                continue;

            if (transform_y > game->z_buffer[x])  // ✅ Skip if behind a wall
                continue;

            for (y = draw_start_y; y < draw_end_y; y++)
            {
                tex_y = (y - draw_start_y) * game->c_ammo_tex[0].height / sprite_height;
                if (tex_y < 0 || tex_y >= game->c_ammo_tex[0].height)
                    continue;

                // ✅ Use the current animated frame
                int frame = c_ammo->animation_index;
                char *pixel = game->c_ammo_tex[frame].addr +
                              (tex_y * game->c_ammo_tex[frame].line_len) +
                              (tex_x * (game->c_ammo_tex[frame].bpp / 8));

                color = 0;
                ft_memcpy(&color, pixel, sizeof(int));

                if ((color & 0x00FFFFFF) != 0)  // ✅ Skip fully transparent pixels
                    my_mlx_pixel_put_b(game, x, y, color);
            }
        }
}



void check_collect_ammo(t_game *game)
{
    for (int i = 0; i < game->c_ammo_count; i++)
    {
        if (!game->c_ammo[i].active) // ✅ Skip inactive c_ammos
            continue;

        int c_ammo_x = (int)game->c_ammo[i].x;
        int c_ammo_y = (int)game->c_ammo[i].y;
        int player_x = (int)game->player.x;
        int player_y = (int)game->player.y;

        if (player_x == c_ammo_x && player_y == c_ammo_y && game->player.ammo < 6)
        {
            game->player.ammo += 3;  // ✅ Heal player
            if (game->player.ammo > 6) 
                game->player.ammo = 6; // ✅ Cap health at 100
            
            game->c_ammo[i].active = 0; // ❌ Remove c_ammo from rendering
        }
    }
}
