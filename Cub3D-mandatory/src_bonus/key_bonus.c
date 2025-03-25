#include "cub3d_bonus.h"

static int	count_key(char **map)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == 'K')
				count++;
	}
	return (count);
}

static void	set_key_info(t_game *game, int x, int y, int index)
{
	game->key[index].x = x + 0.5;
	game->key[index].y = y + 0.5;
	game->key[index].distance = 0;
	game->key[index].visible = 0;
	game->key[index].active = 1;
	game->key[index].animation_index = 0;
	game->key[index].animation_timer = 0;
}

void	set_key_cords(t_game *game)
{
	int	x;
	int	y;
	int	index;

	index = 0;
	game->key_count = count_key(game->map);
	game->key = malloc(sizeof(t_key) * game->key_count);
	if (!game->key)
		print_error("Error: Key allocation failed!");
	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map[y]))
			if (game->map[y][x] == 'K')
				set_key_info(game, x, y, index++);
	}
}

static void	update_key_animation(t_key *key)
{
	if (!key->active)
		return ;
	key->animation_timer++;
	if (key->animation_timer >= 10)
	{
		key->animation_index = (key->animation_index + 1) % 7;
		key->animation_timer = 0;
	}
}

static int	calculate_transform_key(t_game *game, t_key *key,
	double *transform_x, double *transform_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = key->x - game->player.x;
	sprite_y = key->y - game->player.y;
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

static void	calculate_draw_positions(t_game *game, double transform_x,
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

static void	pixel_to_buffer(t_game *game, int tex_x, int x, t_key *key)
{
	int	tex_y;
	int	y;
	int	frame;
	int	color;

	y = key->draw.start_y;
	while (y < key->draw.end_y)
	{
		tex_y = (y - key->draw.start_y) * \
				game->key_tex[0].height / key->draw.height;
		if (tex_y < 0 || tex_y >= game->key_tex[0].height)
		{
			x++;
			continue ;
		}
		frame = key->animation_index;
		color = 0;
		ft_memcpy(&color, game->key_tex[frame].addr \
				+ (tex_y * game->key_tex[frame].line_len) \
				+ (tex_x * (game->key_tex[frame].bpp / 8)), sizeof(int));
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put_b(game, x, y, color);
		y++;
	}
}

void	render_key_pixels(t_game *game, t_key *key,
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
		tex_x = (x - draw->start_x) * game->key_tex[0].width / draw->width;
		if (tex_x < 0 || tex_x >= game->key_tex[0].width || \
		transform_y > game->z_buffer[x])
		{
			x++;
			continue ;
		}
		pixel_to_buffer(game, tex_x, x, key);
		x++;
	}
}

void	render_key(t_game *game, t_key *key)
{
	double	transform_x;
	double	transform_y;

	if (!game->key_tex[0].addr || !key->active)
		return ;
	update_key_animation(key);
	key->distance = pow(game->player.x - key->x, 2) + \
						pow(game->player.y - key->y, 2);
	if (!key->active)
		return ;
	if (!calculate_transform_key(game, key, &transform_x, &transform_y))
		return ;
	calculate_draw_positions(game, transform_x, transform_y, &key->draw);
	render_key_pixels(game, key, &key->draw, transform_y);
}

void	check_collect_key(t_game *game)
{
	int	i;
	int	key_x;
	int	key_y;

	i = -1;
	while (++i < game->key_count)
	{
		if (!game->key[i].active)
			continue ;
		key_x = (int)game->key[i].x;
		key_y = (int)game->key[i].y;
		if ((int)game->player.x == key_x && (int)game->player.y == key_y)
		{
			game->player.key += 1;
			printf("Player total keys: %d\n", game->player.key);
			game->key[i].active = 0;
		}
	}
}
