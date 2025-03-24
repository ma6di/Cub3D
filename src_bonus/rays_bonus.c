

#include "cub3d_bonus.h"

void	calculate_step_b(t_ray *ray, t_game *game)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->side_distx = (game->player.x - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_distx = (ray->mapx + 1.0 - game->player.x) * ray->deltadistx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->side_disty = (game->player.y - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_disty = (ray->mapy + 1.0 - game->player.y) * ray->deltadisty;
	}
}

// void perform_dda_b(t_ray *ray, t_game *game)
// {
//     int door_index;

//     while (ray->mapx >= 0 && ray->mapx < game->width &&
//            ray->mapy >= 0 && ray->mapy < game->height &&
//            (game->map[ray->mapy][ray->mapx] != '1'))  // While inside the map and not hitting a wall
//     {
//         // Check if the ray has hit a door
//         if (game->map[ray->mapy][ray->mapx] == 'D')
//         {
//             door_index = which_door(game, ray->mapy, ray->mapx);
//             if (door_index != -1)  // If door is closed
//             {
//                 ray->door = 1;  // Mark the ray as encountering a door
//                 break;  // Exit the loop if we encounter a door
//             }
//         }
// 		if (game->map[ray->mapy][ray->mapx] == 'Z')
// 		{
// 			ray->zombie = 1;
// 		}
//         // Move the ray (DDA step)
//         if (ray->side_distx < ray->side_disty)
//         {
//             ray->side_distx += ray->deltadistx;
//             ray->mapx += ray->stepx;
//             ray->side = 0;  // The ray is moving along the x-axis
//         }
//         else
//         {
//             ray->side_disty += ray->deltadisty;
//             ray->mapy += ray->stepy;
//             ray->side = 1;  // The ray is moving along the y-axis
//         }
//     }
// }

int	select_door_texture_b(t_ray *ray, t_game *game)
{
	int door_index;
	
		door_index = which_door(game, ray->mapy, ray->mapx);
		if (game->door[door_index].door_state == 1)
			return (DOOR_1);
		else if (game->door[door_index].door_state == 2)
			return (DOOR_2);
		else if (game->door[door_index].door_state == 3)
			return (DOOR_3);
		else if (game->door[door_index].door_state == 4)
			return (DOOR_4);			
		else if (game->door[door_index].door_state == 5)
			return (DOOR_5);
}
void perform_dda_b(t_ray *ray, t_game *game)
{
    int door_index;
    int door_state;
    int tex_x, tex_y;
    int color;
    double hit_pos;

    while (ray->mapx >= 0 && ray->mapx < game->width &&
           ray->mapy >= 0 && ray->mapy < game->height &&
           game->map[ray->mapy][ray->mapx] != '1') // Continue until hitting a wall
    {
        // ✅ Check if the ray hit a door
        if (game->map[ray->mapy][ray->mapx] == 'D')
        {
            door_index = which_door(game, ray->mapy, ray->mapx);
            if (door_index != -1)
            {
                door_state = game->door[door_index].door_state;
                int tex_id = select_door_texture_b(ray, game);

                if (door_state == 1) // Fully closed door
                {
                    ray->door = 1;
                    break;
                }

                // ✅ Compute the exact hit position
                if (ray->side == 0)  // Vertical wall hit
                    hit_pos = game->player.y + ray->walldist * ray->diry;
                else  // Horizontal wall hit
                    hit_pos = game->player.x + ray->walldist * ray->dirx;

                hit_pos -= floor(hit_pos); // Extract fractional part

                // ✅ Compute texture X coordinate
                tex_x = (int)(hit_pos * game->textures[tex_id].width) % game->textures[tex_id].width;
                tex_y = (int)(ray->mapy * game->textures[tex_id].height) % game->textures[tex_id].height;

                // ✅ Get pixel color
                color = *((int *)(game->textures[tex_id].addr +
                                  (tex_y * game->textures[tex_id].line_len) +
                                  (tex_x * (game->textures[tex_id].bpp / 8))));

                // ✅ Check transparency (MiniLibX Alpha Channel)
                if ((color & 0xFF000000) == 0x00000000) // If **NOT** fully transparent, stop ray
                {
                    ray->door = 1;
                    break;
                }
            }
        }
		if (game->map[ray->mapy][ray->mapx] == 'F')
		{
			ray->final_door = 1;
            break;
		}

        // ✅ Move the ray (DDA step)
        if (ray->side_distx < ray->side_disty)
        {
            ray->side_distx += ray->deltadistx;
            ray->mapx += ray->stepx;
            ray->side = 0;
        }
        else
        {
            ray->side_disty += ray->deltadisty;
            ray->mapy += ray->stepy;
            ray->side = 1;
        }
    }
}



void calculate_wall_height_b(t_ray *ray, t_game *game, int x)
{
    // ✅ Ensure we allocate z_buffer
    if (!game->z_buffer)
    {
        game->z_buffer = (double *)malloc(sizeof(double) * SCREEN_WIDTH);
        if (!game->z_buffer)
        {
            print_error("Error: Failed to allocate memory for z_buffer!");
            close_window_b(game);
        }
    }

    // ✅ Calculate perpendicular wall distance
    if (ray->side == 0)
        ray->walldist = (ray->side_distx - ray->deltadistx);
    else
        ray->walldist = (ray->side_disty - ray->deltadisty);

    if (ray->walldist <= 0.001)  // ✅ Prevent division by zero
        ray->walldist = 0.001;

    // ✅ Save wall distance in z_buffer for occlusion checks
    game->z_buffer[x] = ray->walldist;

    // ✅ Calculate wall height
    ray->lineheight = (int)(SCREEN_HEIGHT / ray->walldist);
    ray->drawstart = -ray->lineheight / 2 + SCREEN_HEIGHT / 2;
    if (ray->drawstart < 0)
        ray->drawstart = 0;
    ray->drawend = ray->lineheight / 2 + SCREEN_HEIGHT / 2;
    if (ray->drawend >= SCREEN_HEIGHT)
        ray->drawend = SCREEN_HEIGHT - 1;
}

