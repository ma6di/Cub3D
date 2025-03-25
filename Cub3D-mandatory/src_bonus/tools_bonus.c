/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:42:32 by mcheragh          #+#    #+#             */
/*   Updated: 2025/03/24 14:18:38 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_two_dim_b(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	two_dim_len_b(char **arr)
{
	int	count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count])
		count++;
	return (count);
}

int	select_texture_b(t_ray *ray, t_game *game)
{
	int door_index;
	
	if (ray->door == 1)
	{
		door_index = which_door(game, ray->mapy, ray->mapx);
		ray->door = 0;
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
	if (ray->final_door == 1)
	{
		ray->final_door = 0;
		return (FINAL_DOOR);
	}
	if (ray->side == 0)
	{
		if (ray->dirx > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->diry > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
	return (EAST);
}


int	rgb_to_hex_b(int r, int g, int b)
{
	int	color;

	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	ft_player_health_b(t_game *game)
{
	char	*health;
	char	*phrase;

	health = ft_itoa(game->player.health);
	phrase = ft_strjoin("Health : ", health);
	mlx_string_put(game->mlx, game->win, 20, SCREEN_HEIGHT - SCREEN_HEIGHT / 10, 0xFFFFFF, phrase);
	mlx_string_put(game->mlx, game->win, 21, SCREEN_HEIGHT - SCREEN_HEIGHT / 10, 0xFFFFFF, phrase);
	mlx_string_put(game->mlx, game->win, 20, SCREEN_HEIGHT - SCREEN_HEIGHT / 13, 0xFFFFFF, "Shoot with left control");
	mlx_string_put(game->mlx, game->win, 21, SCREEN_HEIGHT - SCREEN_HEIGHT / 13, 0xFFFFFF, "Shoot with left control");

	free(health);
	free(phrase);
}

int	update_distance(t_game *game, double x, double y)
{
	return (pow(game->player.x - x, 2) + \
		pow(game->player.y - y, 2));

}
