#include "cub3d_bonus.h"

int is_sprite_b(t_game *game, double player_x, double player_y)
{
    int index;
    double tolerance = 0.5;  // ✅ Allow slight overlap (adjust as needed)

    index = 0;
    while (index < game->sprite_count)
    {
        double sprite_x = game->sprites[index].x;
        double sprite_y = game->sprites[index].y;

        // ✅ Check if the player's position is close enough to the sprite
        if (fabs(sprite_x - player_x) < tolerance && fabs(sprite_y - player_y) < tolerance)
        {
            return index;  // ✅ Collision detected
        }
        index++;
    }
    return -1;  // ✅ No collision
}

void check_player_health(t_game *game)
{
	if (is_sprite_b(game, game->player.x, game->player.y) != -1)
		game->player.health -= 2;
	if (game->player.health < 2)
	{
		printf(RED
		"\r\n"
		"\r     🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆\n"
		"\r     🍆        YOU ARE DEAD      🍆\n"
		"\r     🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆🍆\n"
		RESET);
		close_window_b(game);
	}
}

int player_health_index(t_player player)
{	int index;

	if(player.health <= 100 && player.health > 80)
		return 0;
	else if(player.health <= 80 && player.health > 60)
		return 1;
	else if(player.health <= 60 && player.health > 40)
		return 2;
	else if(player.health <= 40 && player.health > 20)
		return 3;
	else if(player.health <= 20)
		return 4;

}
void render_health_bar_b(t_game *game)
{
	int index;
	int x;
    int y;
    int tex_x;
    int tex_y;
    int color;
	int width;
	int height;
	check_player_health(game);
	index = player_health_index(game->player);
    width = game->health_bar[index].width;
    height = game->health_bar[index].height;

    if (!game->health_bar[index].img || !game->health_bar[index].addr)
    {
        printf(RED"Error: health bar texture %d not loaded properly!\n"RESET, index);
        return;
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            tex_x = x;
            tex_y = y;
            color = *((int *)(game->health_bar[index].addr +
                    (tex_y *  game->health_bar[index].line_len + tex_x * (game->health_bar[index].bpp / 8))));

            // ✅ Skip transparent pixels (assuming magenta (0xFF00FF) as transparency)
			if ((color & 0xFF000000) != 0xFF000000)  // If not fully transparent
    			my_mlx_pixel_put_b(game, game->health_bar[index].screen_x + x, game->health_bar[index].screen_y + y, color);
        }
    }
}
