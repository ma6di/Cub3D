
#include "cub3d_bonus.h"

int	count_c_ammo(char **map)
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
			if (map[y][x] == 'A')
			{
				count++;
			}
			x++;
		}
		y++;
	}
	return (count);
}

static void	set_info(t_game *game, int x, int y, int index)
{
	game->c_ammo[index].x = x + 0.5;
	game->c_ammo[index].y = y + 0.5;
	game->c_ammo[index].distance = 0;
	game->c_ammo[index].visible = 0;
	game->c_ammo[index].active = 1;
	game->c_ammo[index].animation_index = 0;
	game->c_ammo[index].animation_timer = 0;
}

void	set_c_ammo_cords(t_game *game)
{
	int	x;
	int	y;
	int	index;

	index = 0;
	game->c_ammo_count = count_c_ammo(game->map);
	game->c_ammo = malloc(sizeof(t_c_ammo) * game->c_ammo_count);
	if (!game->c_ammo)
		print_error("Error: Sprite allocation failed!");
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < ft_strlen(game->map[y]))
		{
			if (game->map[y][x] == 'A')
			{
				set_info(game, x, y, index);
				index++;
			}
			x++;
		}
		y++;
	}
}

void	update_c_ammo_animation(t_c_ammo *c_ammo)
{
	if (!c_ammo->active)
		return ;
	c_ammo->animation_timer++;
	if (c_ammo->animation_timer >= 10)
	{
		c_ammo->animation_index = (c_ammo->animation_index + 1) % 12;
		c_ammo->animation_timer = 0;
	}
}

int	calculate_transform_c_ammo(t_game *game, t_c_ammo *c_ammo,
	double *transform_x, double *transform_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = c_ammo->x - game->player.x;
	sprite_y = c_ammo->y - game->player.y;
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

void	calculate_draw_positions(t_game *game, double transform_x,
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


void	pixel_to_buffer(t_game *game, int tex_x, int x, t_c_ammo *c_ammo)
{
	int	tex_y;
	int	y;
	int	frame;
	int	color;

	y = c_ammo->draw.start_y;
	while (y < c_ammo->draw.end_y)
	{
		tex_y = (y - c_ammo->draw.start_y) * \
				game->c_ammo_tex[0].height / c_ammo->draw.height;
		if (tex_y < 0 || tex_y >= game->c_ammo_tex[0].height)
		{
			x++;
			continue ;
		}
		frame = c_ammo->animation_index;
		color = 0;
		ft_memcpy(&color, game->c_ammo_tex[frame].addr \
				+ (tex_y * game->c_ammo_tex[frame].line_len) \
				+ (tex_x * (game->c_ammo_tex[frame].bpp / 8)), sizeof(int));
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put_b(game, x, y, color);
		y++;
	}
}

void	render_c_ammo_pixels(t_game *game, t_c_ammo *c_ammo,
	t_draw *draw, double transform_y)
{
	int	x;
	int	tex_x;
	int	tex_y;

	x = draw->start_x;
	while (x < draw->end_x)
	{
		if (x < 0 || x >= SCREEN_WIDTH)
		{
			x++;
			continue ;
		}
		tex_x = (x - draw->start_x) * game->c_ammo_tex[0].width / draw->width;
		if (tex_x < 0 || tex_x >= game->c_ammo_tex[0].width || \
		transform_y > game->z_buffer[x])
		{
			x++;
			continue ;
		}
		pixel_to_buffer(game, tex_x, x, c_ammo);
		x++;
	}
}

void render_c_ammo(t_game *game, t_c_ammo *c_ammo)
{
	double	transform_x;
	double	transform_y;

	if (!game->c_ammo_tex[0].addr || !c_ammo->active)
		return ;
	update_c_ammo_animation(c_ammo);
	c_ammo->distance = pow(game->player.x - c_ammo->x, 2) + \
						pow(game->player.y - c_ammo->y, 2);
	if (!c_ammo->active)
		return ;
	if (!calculate_transform_c_ammo(game, c_ammo, &transform_x, &transform_y))
		return ;
	calculate_draw_positions(game, transform_x, transform_y, &c_ammo->draw);
	render_c_ammo_pixels(game, c_ammo, &c_ammo->draw, transform_y);
}

void	check_collect_ammo(t_game *game)
{
	int	i;
	int	c_ammo_x;
	int	c_ammo_y;

	i = 0;
	while (i < game->c_ammo_count)
	{
		if (!game->c_ammo[i].active)
		{
			i++;
			continue ;
		}
		c_ammo_x = (int)game->c_ammo[i].x;
		c_ammo_y = (int)game->c_ammo[i].y;
		if ((int)game->player.x == c_ammo_x && \
			(int)game->player.y == c_ammo_y && game->player.ammo < 6)
		{
			game->player.ammo += 3;
			if (game->player.ammo > 6)
				game->player.ammo = 6;
			game->c_ammo[i].active = 0;
		}
		i++;
	}
}
