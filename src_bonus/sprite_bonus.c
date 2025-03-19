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
                index++;
            }
        }
    }
}

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

void render_sprites(t_game *game)
{
    int i, x, y;
    int tex_x, tex_y, color;
    double sprite_x, sprite_y, inv_det;
    double transform_x, transform_y;
    int sprite_screen_x, sprite_height, sprite_width, draw_start_x, draw_start_y, draw_end_x, draw_end_y;

    if (!game->textures[ZOMBIE].addr)
    {
        printf("Error: Zombie texture is not loaded!\n");
        return;
    }

    // ✅ Update sprite distances
    for (i = 0; i < game->sprite_count; i++)
    {
        game->sprites[i].distance = pow(game->player.x - game->sprites[i].x, 2) +
                                    pow(game->player.y - game->sprites[i].y, 2);
    }

    sort_sprites(game);  // ✅ Sort by distance (farther ones first)

    for (i = 0; i < game->sprite_count; i++)
    {
        sprite_x = game->sprites[i].x - game->player.x;
        sprite_y = game->sprites[i].y - game->player.y;

        inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - game->player.dir_x * game->player.plane_y);
        transform_x = inv_det * (game->player.dir_y * sprite_x - game->player.dir_x * sprite_y);
        transform_y = inv_det * (-game->player.plane_y * sprite_x + game->player.plane_x * sprite_y);

        // ✅ Skip sprites behind the player
        if (transform_y <= 0)
            continue;

        sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + transform_x / transform_y));
        sprite_height = abs((int)(SCREEN_HEIGHT / transform_y)) / 2;
        sprite_width = abs((int)(SCREEN_WIDTH / transform_y)) / 2;


		// ray->lineheight = (int)(SCREEN_HEIGHT / ray->walldist);
    	// ray->drawstart = -ray->lineheight / 2 + SCREEN_HEIGHT / 2;
        // ✅ Fix Sprite Positioning
        draw_start_y = SCREEN_HEIGHT / 2 + 10;
        draw_end_y = draw_start_y + sprite_height;
        draw_start_x = sprite_screen_x - sprite_width / 2;
        draw_end_x = sprite_screen_x + sprite_width / 2;

        for (x = draw_start_x; x < draw_end_x; x++)
        {
            if (x < 0 || x >= SCREEN_WIDTH)  // ✅ Skip out-of-bounds columns
                continue;

            tex_x = (x - draw_start_x) * game->textures[ZOMBIE].width / sprite_width;
            if (tex_x < 0 || tex_x >= game->textures[ZOMBIE].width)
                continue;  // ✅ Bounds check

            // ✅ Don't draw the sprite if it's behind a wall
            if (transform_y > game->z_buffer[x])  
                continue;

            for (y = draw_start_y; y < draw_end_y; y++)
            {
                tex_y = (y - draw_start_y) * game->textures[ZOMBIE].height / sprite_height;
                if (tex_y < 0 || tex_y >= game->textures[ZOMBIE].height)
                    continue;  // ✅ Bounds check

                // ✅ Safe pixel retrieval
                char *pixel = game->textures[ZOMBIE].addr +
                    (tex_y * game->textures[ZOMBIE].line_len) +
                    (tex_x * (game->textures[ZOMBIE].bpp / 8));

                color = 0;
                ft_memcpy(&color, pixel, sizeof(int));

                if ((color & 0x00FFFFFF) != 0)  // ✅ Skip fully transparent pixels
                    my_mlx_pixel_put_b(game, x, y, color);
            }
        }
    }
}


                // if ((color & 0x00FFFFFF) != 0)  // ✅ Skip fully transparent pixels

int can_move_sprite(t_game *game, double new_x, double new_y)
{
    double half_size = 0.2;  // ✅ Adjust based on sprite size

    // ✅ Block movement if center is inside a wall
    if (game->map[(int)new_y][(int)new_x] == '1' ||
        game->map[(int)new_y][(int)new_x] == 'D')
        return (0);

    // ✅ Check sprite's four corners for wall collisions
    if ((game->map[(int)(new_y - half_size)][(int)new_x] && \
		game->map[(int)(new_y - half_size)][(int)new_x] == '1') || 
        (game->map[(int)(new_y + half_size)][(int)new_x] && \
		game->map[(int)(new_y + half_size)][(int)new_x] == '1')|| 
        (game->map[(int)new_y][(int)(new_x - half_size)] && \
		game->map[(int)new_y][(int)(new_x - half_size)] == '1') || 
        (game->map[(int)new_y][(int)(new_x + half_size)] && \
		game->map[(int)new_y][(int)(new_x + half_size)] == '1')) 
		
        return (0);  

    return (1);  // ✅ Sprite can move
}



void move_sprites(t_game *game)
{
    int i;
    double dir_x, dir_y, length;
    double next_x, next_y;
    double move_step = 0.01;  // ✅ Small step size to avoid skipping walls
	int can_move_x;
	int can_move_y;

    for (i = 0; i < game->sprite_count; i++)
    {
        // if (!game->sprites[i].active) // ✅ Skip inactive sprites
        //     continue;

        // ✅ Calculate direction vector (normalized)
        dir_x = game->player.x - game->sprites[i].x;
        dir_y = game->player.y - game->sprites[i].y;
        length = sqrt(dir_x * dir_x + dir_y * dir_y);
        if (length == 0) // ✅ Prevent division by zero
            continue;

        dir_x /= length;
        dir_y /= length;

        // ✅ Compute new positions
        next_x = game->sprites[i].x + dir_x * move_step;
        next_y = game->sprites[i].y + dir_y * move_step;

        // ✅ Check for wall collision
		can_move_x = can_move_sprite(game, next_x, game->sprites[i].y);
		can_move_y = can_move_sprite(game, game->sprites[i].x, next_y);

        if (can_move_x && can_move_y)
        {
            // ✅ Move normally if no obstacles
            game->sprites[i].x = next_x;
            game->sprites[i].y = next_y;
        }
        else if (can_move_x)
        {
            // ✅ Slide along X-axis if Y is blocked
            game->sprites[i].x = next_x;
        }
        else if (can_move_y)
        {
            // ✅ Slide along Y-axis if X is blocked
            game->sprites[i].y = next_y;
        }
    }
}




