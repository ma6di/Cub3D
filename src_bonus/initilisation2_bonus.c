#include "cub3d_bonus.h"

void	init_ray_b(t_ray *ray)
{
	ray->dirx = 0;
	ray->diry = 0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->side_distx = 0;
	ray->side_disty = 0;
	ray->deltadistx = 0;
	ray->deltadisty = 0;
	ray->walldist = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->side = 0;
	ray->lineheight = 0;
	ray->drawstart = 0;
	ray->drawend = 0;
	ray->camera_x = 0;
	ray->door = 0;
	ray->zombie = 0;
}

void	init_mlx_ray_b(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dirx = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->diry = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->mapx = (int)game->player.x;
	ray->mapy = (int)game->player.y;
	if (ray->dirx == 0)
		ray->deltadistx = 1e30;
	else
		ray->deltadistx = fabs(1 / ray->dirx);
	if (ray->diry == 0)
		ray->deltadisty = 1e30;
	else
		ray->deltadisty = fabs(1 / ray->diry);
	calculate_step_b(ray, game);
}

void init_gun_b(t_gun *gun, int dim, int index)
{
	gun[index].addr = NULL;
	gun[index].img = NULL;
	gun[index].path = NULL;
	gun[index].height = dim;
	gun[index].width = dim;
    gun[index].screen_x = 0;
    gun[index].screen_y = 0;
	gun[index].screen_x = (SCREEN_WIDTH / 2) - (gun[index].width / 2);  // ✅ Center horizontally
    gun[index].screen_y = SCREEN_HEIGHT - gun[index].height;           // ✅ Position at bottom
}