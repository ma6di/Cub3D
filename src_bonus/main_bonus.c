

#include "cub3d_bonus.h"

typedef struct s_renderable
{
    double distance;  // Distance from player
    int type;         // Type: 0 = wall, 1 = sprite, 2 = heart, 3 = ammo, etc.
    void *object;     // Pointer to the actual object (sprite, wall, etc.)
} t_renderable;

int compare_renderables(const void *a, const void *b)
{
    double dist_a = ((t_renderable *)a)->distance;
    double dist_b = ((t_renderable *)b)->distance;
    return (dist_b - dist_a);  // Sort by descending distance
}
int render_b(t_game *game)
{
    mlx_clear_window(game->mlx, game->win);

    int num_renderables = game->sprite_count + game->heart_count + game->c_ammo_count + game->key_count;
    t_renderable renderables[num_renderables];

    int index = 0;

    // ✅ Step 1: Store objects in array
    for (int i = 0; i < game->sprite_count; i++)
    {
        renderables[index].distance = game->sprites[i].distance;
        renderables[index].type = 1;
        renderables[index].object = &game->sprites[i];
        index++;
    }
    for (int i = 0; i < game->heart_count; i++)
    {
        renderables[index].distance = game->heart[i].distance;
        renderables[index].type = 2;
        renderables[index].object = &game->heart[i];
        index++;
    }
    for (int i = 0; i < game->c_ammo_count; i++)
    {
        renderables[index].distance = game->c_ammo[i].distance;
        renderables[index].type = 3;
        renderables[index].object = &game->c_ammo[i];
        index++;
    }
    for (int i = 0; i < game->key_count; i++)
    {
        renderables[index].distance = game->key[i].distance;
        renderables[index].type = 4;
        renderables[index].object = &game->key[i];
        index++;
    }

    // ✅ Step 2: Sort objects by distance (farthest first)
    qsort(renderables, num_renderables, sizeof(t_renderable), compare_renderables);

    // ✅ Step 3: Draw background
    if (game->color[CEILING].col_tex_str)
        draw_floor_and_ceiling_b(game, CEILING);
    else
        draw_floor_and_ceiling_b(game, SKY);
    draw_floor_and_ceiling_b(game, FLOOR);

    // ✅ Step 4: Cast rays for walls
    cast_rays_b(game);
    minimap_b(game);
    update_player_b(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    // ✅ Step 5: Render sorted objects in correct order
    for (int i = 0; i < num_renderables; i++)
    {
        if (renderables[i].type == 1)
            render_sprites(game, (t_sprite *)renderables[i].object);
        else if (renderables[i].type == 2)
            render_hearts(game, (t_heart *)renderables[i].object);
        else if (renderables[i].type == 3)
            render_c_ammo(game, (t_c_ammo *)renderables[i].object);
        else if (renderables[i].type == 4)
            render_key(game, (t_key *)renderables[i].object);
    }

    // ✅ Step 6: Move & update other elements
    move_sprites(game);
    render_health_bar_b(game);
    render_ammo_bar_b(game);
    draw_gun_b(game);
	return 0;
}


int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		print_error(RED"Error: Please provide a map file\n"RESET);
		return (1);
	}
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		print_error(RED"Error: Memory allocation failed\n"RESET);
		return (1);
	}
	init_game_b(game);
	if (!pars_file_b(argv[1], game, argv))
	{
		close_window_b(game);
		return (1);
	}
	print_struct_b(game);
	create_window_b(game);
	close_window_b(game);
	return (0);
}
