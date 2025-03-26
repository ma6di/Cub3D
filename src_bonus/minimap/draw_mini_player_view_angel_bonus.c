
#include "cub3d_bonus.h"

static void	update_line_vars(t_line *line)
{
	line->e2 = 2 * line->err;
	if (line->e2 > -line->dy)
	{
		line->err -= line->dy;
		line->x0 += (line->x0 < line->x1) ? 1 : -1;
	}
	if (line->e2 < line->dx)
	{
		line->err += line->dx;
		line->y0 += (line->y0 < line->y1) ? 1 : -1;
	}
}

void	draw_line_b(t_game *game, t_line *line, int color)
{
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	line->err = line->dx - line->dy;
	while (1)
	{
		if (line->x0 >= 0 && line->y0 >= 0
			&& line->x0 < MAX_MINIMAP_WIDTH * game->minimap.tile_size
			&& line->y0 < MAX_MINIMAP_HEIGHT * game->minimap.tile_size)
		{
			draw_tile_b(game, line->x0, line->y0, color);
		}
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		update_line_vars(line);
	}
}


void	draw_player_b(t_game *game)
{
	int	px;
	int	py;
	int	start_x;
	int	start_y;

	calculate_minimap_bounds(game, &start_x, NULL, &start_y, NULL);
	px = ((int)game->player.x - start_x) * game->minimap.tile_size;
	py = ((int)game->player.y - start_y) * game->minimap.tile_size;

	draw_view_angle_b(game, px, py);
	draw_tile_b(game, px, py, 0xffd700);
}

void	draw_view_angle_b(t_game *game, int px, int py)
{
	t_line	line;
	t_view	v;

	v.view_dist = 15;
	v.base_w = 5;
	line.x0 = px;
	line.y0 = py;
	line.x1 = px + (int)(v.view_dist * game->player.dir_x);
	line.y1 = py + (int)(v.view_dist * game->player.dir_y);
	draw_line_b(game, &line, LIGHTBLUE);
	v.perp_x = (int)(v.base_w * -game->player.dir_y);
	v.perp_y = (int)(v.base_w * game->player.dir_x);
	v.bx1 = line.x1 + v.perp_x;
	v.by1 = line.y1 + v.perp_y;
	v.bx2 = line.x1 - v.perp_x;
	v.by2 = line.y1 - v.perp_y;
	line.x1 = v.bx1;
	line.y1 = v.by1;
	draw_line_b(game, &line, LIGHTBLUE);
	line.x1 = v.bx2;
	line.y1 = v.by2;
	draw_line_b(game, &line, LIGHTBLUE);
}
