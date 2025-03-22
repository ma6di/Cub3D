
#include "cub3d_bonus.h"

int	count_hearts(char **map)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'H')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	set_heart_info(t_game *game, int x, int y, int index)
{
	game->heart[index].x = x + 0.5;
	game->heart[index].y = y + 0.5;
	game->heart[index].distance = 0;
	game->heart[index].visible = 0;
	game->heart[index].active = 1;
	game->heart[index].animation_index = 0;
	game->heart[index].animation_timer = 0;
}

void	set_heart_cords(t_game *game)
{
	int	x;
	int	y;
	int	index;

	index = 0;
	game->heart_count = count_hearts(game->map);
	game->heart = malloc(sizeof(t_heart) * game->heart_count);
	if (!game->heart)
		print_error("Error: Memory allocation for hearts failed!");
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < ft_strlen(game->map[y]))
		{
			if (game->map[y][x] == 'H')
			{
				set_heart_info(game, x, y, index);
				index++;
			}
			x++;
		}
		y++;
	}
}

void	update_heart_animation(t_heart *heart)
{
	if (!heart->active)
		return ;
	heart->animation_timer++;
	if (heart->animation_timer >= 10)
	{
		heart->animation_index = (heart->animation_index + 1) % 12;
		heart->animation_timer = 0;
	}
}

int	calculate_transform_heart(t_game *game, t_heart *heart,
	double *transform_x, double *transform_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = heart->x - game->player.x;
	sprite_y = heart->y - game->player.y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	*transform_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	*transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
	if (*transform_y <= 0)
		return (0);
	return (1);
}

void	calculate_draw_positions_heart(t_game *game, double transform_x,
	double transform_y, t_draw *draw)
{
	double	scale;

	scale = 0.15;
	draw->screen_x = (int)((SCREEN_WIDTH / 2)
			* (1 + transform_x / transform_y));
	draw->height = abs((int)(SCREEN_HEIGHT / transform_y)) * scale;
	draw->width = abs((int)(SCREEN_WIDTH / transform_y)) * scale;
	draw->start_y = SCREEN_HEIGHT / 2 + 20;
	draw->end_y = draw->start_y + draw->height;
	draw->start_x = draw->screen_x - draw->width / 2;
	draw->end_x = draw->screen_x + draw->width / 2;
}

void	pixel_to_buffer_heart(t_game *game, int tex_x, int x, t_heart *heart)
{
	int	tex_y;
	int	y;
	int	frame;
	int	color;

	y = heart->draw.start_y;
	while (y < heart->draw.end_y)
	{
		tex_y = (y - heart->draw.start_y) * \
				game->heart_tex[0].height / heart->draw.height;
		if (tex_y < 0 || tex_y >= game->heart_tex[0].height)
		{
			x++;
			continue ;
		}
		frame = heart->animation_index;
		color = 0;
		ft_memcpy(&color, game->heart_tex[frame].addr \
				+ (tex_y * game->heart_tex[frame].line_len) \
				+ (tex_x * (game->heart_tex[frame].bpp / 8)), sizeof(int));
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put_b(game, x, y, color);
		y++;
	}
}

void	render_heart_pixels(t_game *game, t_heart *heart,
	t_draw *draw, double transform_y)
{
	int	x;
	int	tex_x;

	x = draw->start_x;
	while (x < draw->end_x)
	{
		if (x < 0 || x >= SCREEN_WIDTH)
		{
			x++;
			continue ;
		}
		tex_x = (x - draw->start_x) * game->heart_tex[0].width / draw->width;
		if (tex_x < 0 || tex_x >= game->heart_tex[0].width || \
		transform_y > game->z_buffer[x])
		{
			x++;
			continue ;
		}
		pixel_to_buffer_heart(game, tex_x, x, heart);
		x++;
	}
}

void	render_hearts(t_game *game, t_heart *heart)
{
	double	transform_x;
	double	transform_y;

	if (!game->heart_tex[0].addr || !heart->active)
		return ;
	update_heart_animation(heart);
	heart->distance = pow(game->player.x - heart->x, 2) + \
						pow(game->player.y - heart->y, 2);
	if (!heart->active)
		return ;
	if (!calculate_transform_heart(game, heart, &transform_x, &transform_y))
		return ;
	calculate_draw_positions_heart(game, transform_x, transform_y, \
									&heart->draw);
	render_heart_pixels(game, heart, &heart->draw, transform_y);
}

void	check_collect_hearts(t_game *game)
{
	int	i;
	int	heart_x;
	int	heart_y;

	i = 0;
	while (i < game->heart_count)
	{
		if (!game->heart[i].active)
		{
			i++;
			continue ;
		}
		heart_x = (int)game->heart[i].x;
		heart_y = (int)game->heart[i].y;
		if ((int)game->player.x == heart_x && \
			(int)game->player.y == heart_y && game->player.health < 100)
		{
			game->player.health += 20;
			if (game->player.health > 100)
				game->player.health = 100;
			game->heart[i].active = 0;
		}
		i++;
	}
}

