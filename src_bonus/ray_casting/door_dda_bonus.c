
#include "cub3d_bonus.h"

static int	select_door_texture_b(t_ray *ray, t_game *game)
{
	int	door_index;

	door_index = which_door(game, ray->mapy, ray->mapx);
	if (game->door[door_index].door_state == 1)
		return (DOOR_1);
	else if (game->door[door_index].door_state == 2)
		return (DOOR_2);
	else if (game->door[door_index].door_state == 3)
		return (DOOR_3);
	else if (game->door[door_index].door_state == 4)
		return (DOOR_4);
	else
		return (DOOR_5);
}

static int	handle_door_state(t_game *game, int door_index)
{
	int	door_state;

	door_state = game->door[door_index].door_state;
	if (door_state == 1)
		return (1);
	if (door_state >= 2 && door_state <= 4)
		return (2);
	return (0);
}

static int	handle_door_hit_texture(t_ray *ray, t_game *game, int tex_id)
{
	int		tex_x;
	int		tex_y;
	int		color;
	double	hit_pos;

	if (ray->side == 0)
		hit_pos = game->player.y + ray->walldist * ray->diry;
	else
		hit_pos = game->player.x + ray->walldist * ray->dirx;
	hit_pos -= floor(hit_pos);
	tex_x = (int)(hit_pos * game->textures[tex_id].width) 
		% game->textures[tex_id].width;
	tex_y = (int)(ray->mapy * game->textures[tex_id].height) 
		% game->textures[tex_id].height;
	color = *((int *)(game->textures[tex_id].addr \
			+ (tex_y * game->textures[tex_id].line_len) \
			+ (tex_x * (game->textures[tex_id].bpp / 8))));
	if ((color & 0xFF000000) == 0x00000000)
		return (1);
	return (0);
}

int	handle_door_hit(t_ray *ray, t_game *game)
{
	int	door_index;
	int	door_state;
	int	tex_id;

	door_index = which_door(game, ray->mapy, ray->mapx);
	if (door_index == -1)
		return (0);

	door_state = handle_door_state(game, door_index);
	if (door_state == 1)
	{
		ray->door = 1;
		return (1);
	}
	tex_id = select_door_texture_b(ray, game);
	if (door_state == 2)
	{
		if (handle_door_hit_texture(ray, game, tex_id))
		{
			ray->door = 1;
			return (1);
		}
	}
	return (0);
}