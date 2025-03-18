#include "cub3d_bonus.h"

int	get_wall_texture_pixel_b(t_texture *texture, int x, int y, int tex_id)
{
	char	*dst;
	int		color;

	if (!texture || tex_id < 0 || tex_id >= 6)
	{
		print_error(RED"Error: Invalid texture ID %d\n"RESET, tex_id);
		return (-1);
	}
	if (!texture[tex_id].addr)
	{
		print_error("Error: texture[%d].addr is NULL\n", tex_id);
		return (-1);
	}
	if (x < 0 || x >= texture[tex_id].width || y < 0 || \
		y >= texture[tex_id].height)
	{
		print_error(RED"Error: Invalid coordinates for texture\n"RESET);
		return (-1);
	}
	dst = texture[tex_id].addr + (y * texture[tex_id].line_len + \
			x * (texture[tex_id].bpp / 8));
	color = 0;
	ft_memcpy(&color, dst, sizeof(int));
	return (color);
}

void	my_mlx_pixel_put_b(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		//print_error(RED"Error: Pixel (%d, %d) out of bounds!\n"RESET, x, y);
		return ;
	}

	if (!game->img || !game->addr)
	{
		print_error(RED"Error: Image buffer is not initialized!\n"RESET);
		return ;
	}
	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}


static void	calculate_texture_params_b(t_game *game, t_ray *ray, int tex_id, \
									t_texture_params *params)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->walldist * ray->diry;
	else
		wall_x = game->player.x + ray->walldist * ray->dirx;
	wall_x -= floor(wall_x);
	params->tex_x = (int)(wall_x * game->textures[tex_id].width);
	if (params->tex_x < 0)
		params->tex_x = 0;
	if (params->tex_x >= game->textures[tex_id].width)
		params->tex_x = game->textures[tex_id].width - 1;
	params->step = (double)game->textures[tex_id].height / ray->lineheight;
	params->tex_pos = (ray->drawstart - SCREEN_HEIGHT / 2 + \
						ray->lineheight / 2) * params->step;
}

static void	render_wall_slice_b(t_game *game, t_ray *ray, int x, int tex_id)
{
	t_texture_params	params;
	int					tex_y;
	int					color;
	int					y;

	y = ray->drawstart;
	calculate_texture_params_b(game, ray, tex_id, &params);
	while (y < ray->drawend)
	{
		if (y < 0 || y >= SCREEN_HEIGHT)
			continue ;
		tex_y = (int)fmod(params.tex_pos, game->textures[tex_id].height);
		params.tex_pos += params.step;
		color = get_wall_texture_pixel_b(game->textures, params.tex_x, \
										tex_y, tex_id);
		my_mlx_pixel_put_b(game, x, y, color);
		y++;
	}
}

// void render_zombie(t_game *game, t_ray *ray)
// {
//     int x, y;
//     int tex_x, tex_y;
//     int color;
//     int width = game->textures[ZOMBIE].width;
//     int height = game->textures[ZOMBIE].height;

//     // ✅ Calculate distance from player to zombie (avoid division by zero)
//     double distance = sqrt(pow(ray->mapx - game->player.x, 2) + pow(ray->mapy - game->player.y, 2));
//     if (distance < 0.1)  // Prevent extreme close rendering issues
//         return;

//     // ✅ Scale sprite size based on distance
//     int sprite_size = (int)(TILE_SIZE / distance * 10); // Adjust 150 for proper scaling
//     if (sprite_size < 10) // ✅ Prevent rendering when too small
//         return;

//     // ✅ Convert world coordinates to screen coordinates
//     int screen_x = (ray->mapx - game->player.x) * TILE_SIZE + SCREEN_WIDTH / 2;
//     int screen_y = (ray->mapy - game->player.y) * TILE_SIZE + SCREEN_HEIGHT / 2;

//     // ✅ Ensure sprite is centered
//     screen_x -= sprite_size / 2;
//     screen_y -= sprite_size / 2;

//     for (y = 0; y < sprite_size; y++)
//     {
//         int draw_y = screen_y + y;
//         if (draw_y < 0 || draw_y >= SCREEN_HEIGHT) // ✅ Prevent out-of-bounds drawing
//             continue;

//         for (x = 0; x < sprite_size; x++)
//         {
//             int draw_x = screen_x + x;
//             if (draw_x < 0 || draw_x >= SCREEN_WIDTH) // ✅ Prevent out-of-bounds drawing
//                 continue;

//             // ✅ Scale texture coordinates
//             tex_x = (x * width) / sprite_size;
//             tex_y = (y * height) / sprite_size;

//             color = *((int *)(game->textures[ZOMBIE].addr +
//                     (tex_y * game->textures[ZOMBIE].line_len + tex_x * (game->textures[ZOMBIE].bpp / 8))));

//             // ✅ Check transparency correctly
//            if ((color & 0xFF000000) != 0xFF000000)  // If NOT fully transparent
//                 my_mlx_pixel_put_b(game, draw_x, draw_y, color);
//         }
//     }
// }



void	cast_rays_b(t_game *game)
{
	t_ray	ray;
	int		x;
	int		y;
	int		color;
	int		tex_id;

	init_ray_b(&ray);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_mlx_ray_b(&ray, game, x);
		calculate_step_b(&ray, game);
		perform_dda_b(&ray, game);
		calculate_wall_height_b(&ray, game);
		tex_id = select_texture_b(&ray, game);
		// if(tex_id == ZOMBIE)
		// 	render_zombie(game, &ray);
		// else
			render_wall_slice_b(game, &ray, x, tex_id);
		x++;
	}
}
