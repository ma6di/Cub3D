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


static int	is_wall_or_closed_door(t_game *game, int x, int y)
{
	int	door_index;

	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == 'D')
	{
		door_index = which_door(game, y, x);
		if (door_index == -1 || game->door[door_index].door_state == 0)
			return (1);
	}
	return (0);
}

static int	is_too_close_to_wall_or_door(t_game *game, double x, double y)
{
	double	offsets[4][2];
	int		i;
	int		new_x;
	int		new_y;

	offsets[0][0] = 0;
	offsets[0][1] = 0.3;
	offsets[1][0] = 0.3;
	offsets[1][1] = 0;
	offsets[2][0] = 0;
	offsets[2][1] = -0.3;
	offsets[3][0] = -0.3;
	offsets[3][1] = 0;
	i = -1;
	while (++i < 4)
	{
		new_x = (int)(x + offsets[i][0]);
		new_y = (int)(y + offsets[i][1]);
		if (is_wall_or_closed_door(game, new_x, new_y))
			return (1);
	}
	return (0);
}

int	can_move_sprite(t_game *game, double new_x, double new_y)
{
	if (is_wall_or_closed_door(game, (int)new_x, (int)new_y))
		return (0);
	if (is_too_close_to_wall_or_door(game, new_x, new_y))
		return (0);
	return (1);
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

t_sprite *get_zombie_in_front(t_game *game)
{
    double range = 7.0; // ✅ Shooting range
    double min_shoot_angle = 0.3; // ✅ Adjust this for a wider cone

    for (int i = 0; i < game->sprite_count; i++)
    {
        t_sprite *zombie = &game->sprites[i];

        if (!zombie->active) // ✅ Skip dead zombies
            continue;

        double dx = zombie->x - game->player.x;
        double dy = zombie->y - game->player.y;
        double distance = sqrtf(dx * dx + dy * dy);

        if (distance < range)
        {
            double dot = (dx * game->player.dir_x + dy * game->player.dir_y) / distance; // ✅ Cosine of angle
            if (dot > min_shoot_angle) // ✅ If within shooting angle
                return zombie;
        }
    }
    return NULL; // ❌ No zombie in front
}


void remove_zombie(t_game *game, int index)
{
    if (index < 0 || index >= game->sprite_count)
        return;

    // ✅ Shift all zombies after the index forward
    for (int i = index; i < game->sprite_count - 1; i++)
       		game->sprites[i] = game->sprites[i + 1];

    game->sprite_count--;  // ✅ Reduce total count
}



