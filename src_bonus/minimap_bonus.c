/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:16:17 by mit          #+#    #+#             */
/*   Updated: 2025/02/19 14:46:31 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_mini(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int screen_x;
	int screen_y;

	j = 0;
	while (j < game->minimap.tile_size)
	{
		i = 0;
		while (i < game->minimap.tile_size)
		{
			screen_x = x + i + game->minimap.offset_x;
			screen_y = y + j + game->minimap.offset_y;
			my_mlx_pixel_put(game, screen_x, screen_y, color);
			i++;
		}
		j++;
	}
}

static void	draw_minimap_tiles(t_game *game)
{
	int		map_y;
	int		map_x;
	int		x;
	int		y;
	char	tile;

	map_y = 0;
	while (map_y < game->height && game->map[map_y])
	{
		map_x = 0;
		while (map_x < game->width && game->map[map_y][map_x])
		{
			x = map_x * game->minimap.tile_size;
			y = map_y * game->minimap.tile_size;
			tile = game->map[map_y][map_x];
			if (tile == '1')
				draw_mini(game, x, y, 0xF00FFF);
			else if (tile == '0' || tile == 'N' || tile == 'W' || tile == 'E' || tile == 'S')
				draw_mini(game, x, y, 0xFFFFFF);
			else if (tile == 'D')
				draw_mini(game, x, y, 0xFF0000);
			map_x++;
		}
		map_y++;
	}
}

static void	draw_player_on_minimap(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = (int)(game->player.x * game->minimap.tile_size) - 3;
	player_y = (int)(game->player.y * game->minimap.tile_size) - 3;
	if (player_x >= 0 && player_y >= 0 && \
		player_x < game->width * game->minimap.tile_size && \
		player_y < game->height * game->minimap.tile_size)
	{
		draw_mini(game, player_x, player_y, 0xffd700);
	}
}

void	minimap(t_game *game)
{
	draw_minimap_tiles(game);
	draw_player_on_minimap(game);
}

