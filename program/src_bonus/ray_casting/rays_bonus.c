/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:59:30 by mcheragh          #+#    #+#             */
/*   Updated: 2025/04/01 17:59:31 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	perform_dda_b(t_ray *ray, t_game *game)
{
	while (ray->mapx >= 0 && ray->mapx < game->width && ray->mapy >= 0 && \
		ray->mapy < game->height && game->map[ray->mapy][ray->mapx] != '1')
	{
		if (game->map[ray->mapy][ray->mapx] == 'D' || \
			game->map[ray->mapy][ray->mapx] == 'F')
		{
			if (handle_door_hit(ray, game))
				break ;
		}
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

void	calculate_wall_height_b(t_ray *ray, t_game *game, int x)
{
	if (!game->z_buffer)
	{
		game->z_buffer = (double *)malloc(sizeof(double) * SCREEN_WIDTH);
		if (!game->z_buffer)
		{
			print_error("Error: Failed to allocate memory for z_buffer!");
			close_window_b(game);
		}
	}
	if (ray->side == 0)
		ray->walldist = (ray->side_distx - ray->deltadistx);
	else
		ray->walldist = (ray->side_disty - ray->deltadisty);
	if (ray->walldist <= 0.001)
		ray->walldist = 0.001;
	game->z_buffer[x] = ray->walldist;
	ray->lineheight = (int)(SCREEN_HEIGHT / ray->walldist);
	ray->drawstart = -ray->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (ray->drawend >= SCREEN_HEIGHT)
		ray->drawend = SCREEN_HEIGHT - 1;
}
