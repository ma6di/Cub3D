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

static void	draw_mini_b(t_game *game, int x, int y, int color)
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
			my_mlx_pixel_put_b(game, screen_x, screen_y, color);
			i++;
		}
		j++;
	}
}

static void	draw_minimap_tiles_b(t_game *game)
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
			// if (tile == '1')
			//  	draw_mini_b(game, x, y, 0xF00FFF);
			if (tile == '0' || tile == 'N' || tile == 'W' || tile == 'E' || tile == 'S' || \
			tile == 'Z' || tile == 'A' || tile == 'K' || tile == 'H')
				draw_mini_b(game, x, y, 0xFFFFFF);
			else if (tile == 'D')
				draw_mini_b(game, x, y, 0xFF0000);
			map_x++;
		}
		map_y++;
	}
}

void draw_line_b(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        draw_mini_b(game, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_player_view_angle_b(t_game *game, int player_x, int player_y)
{
    int view_distance = 15; // Distance of the view angle
    int base_half_width = 5; // Half-width of the base of the triangle

    // Apex of the triangle (player's position)
    int apex_x = player_x;
    int apex_y = player_y;

    // Calculate the base center of the triangle
    int base_center_x = apex_x + (int)(view_distance * game->player.dir_x);
    int base_center_y = apex_y + (int)(view_distance * game->player.dir_y);

    // Calculate the perpendicular direction for the base of the triangle
    int perp_dir_x = (int)(base_half_width * -game->player.dir_y);
    int perp_dir_y = (int)(base_half_width * game->player.dir_x);

    // Calculate the coordinates of the base vertices
    int base_x1 = base_center_x + perp_dir_x;
    int base_y1 = base_center_y + perp_dir_y;
    int base_x2 = base_center_x - perp_dir_x;
    int base_y2 = base_center_y - perp_dir_y;

    // Draw the triangle
    draw_line_b(game, player_x, player_y, apex_x, apex_y, LIGHTBLUE); // Light blue color
    draw_line_b(game, player_x, player_y, base_x1, base_y1, LIGHTBLUE);
    draw_line_b(game, player_x, player_y, base_x2, base_y2, LIGHTBLUE);
    draw_line_b(game, base_x1, base_y1, apex_x, apex_y, LIGHTBLUE);
    draw_line_b(game, base_x2, base_y2, apex_x, apex_y, LIGHTBLUE);
}

void draw_player_view_point_b(t_game *game, int player_x, int player_y)
{
    int view_distance = 15; // Distance of the view angle

    // Calculate the end coordinates of the view angle using plane_x and plane_y
    double x2 = player_x + (int)(view_distance * game->player.dir_x);
    double y2 = player_y + (int)(view_distance * game->player.dir_y);

    // Draw the view angle
	draw_line_b(game, player_x, player_y, x2, y2, LIGHTBLUE);
}

static void	draw_player_on_minimap_b(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = (int)(game->player.x * game->minimap.tile_size) - 3;
	player_y = (int)(game->player.y * game->minimap.tile_size) - 3;
	draw_player_view_angle_b(game, player_x, player_y);
	draw_player_view_point_b(game, player_x, player_y);
	if (player_x >= 0 && player_y >= 0 && \
		player_x < game->width * game->minimap.tile_size && \
		player_y < game->height * game->minimap.tile_size)
	{
		draw_mini_b(game, player_x, player_y, 0xffd700);
	}
}

static void	draw_walls_b(t_game *game)
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
				draw_mini_b(game, x, y, 0xF00FFF);
			// else if (tile == '0' || tile == 'N' || tile == 'W' || tile == 'E' || tile == 'S')
			// 	draw_mini(game, x, y, 0xFFFFFF);
			// else if (tile == 'D')
			// 	draw_mini(game, x, y, 0xFF0000);
			map_x++;
		}
		map_y++;
	}
}

void	minimap_b(t_game *game)
{
	draw_minimap_tiles_b(game);
	draw_player_on_minimap_b(game);
	draw_walls_b(game);
}


