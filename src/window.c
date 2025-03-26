

#include "cub3D.h"

/*
 * Handles closing the game window.
 * Destroys the MLX display and exits the program.
 * 
 * Parameters:
 * - game: Pointer to the main game structure.
 */
// int close_window(t_game *game)
// {
//     mlx_destroy_display(game->mlx);
//     exit(0);
// }


/*
 * Creates and initializes the game window, textures, and rendering system.
 * Also sets up MLX hooks for user input and rendering.
 * 
 * Parameters:
 * - game: Pointer to the main game structure.
 */
void create_window(t_game *game)
{
    // Initialize player data
    load_player(game);

    // Initialize MLX
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        print_error("Error! MLX initialization failed!");
        return;
    }

    // Create the game window
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
    if (!game->win)
    {
        free(game->mlx); // Don't call `mlx_destroy_display()`
        print_error("Error! MLX window creation failed!");
        return;
    }

    // Initialize framebuffer for rendering
	//game->img stores the main rendering buffer (where we draw the screen).
    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game->img)
    {
        print_error("Error: mlx_new_image() failed!\n");
        return;
    }
	//game->addr is a pointer to the pixel data of game->img
    game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_len, &game->endian);

    // Initialize player positioning and direction
    game->player.x += 0.5;
    game->player.y += 0.5;
    // Load wall textures
	//Each game->textures[] holds a different texture image.
    init_mlx_wall_texture(game, NORTH, game->textures[NORTH].path);
    init_mlx_wall_texture(game, SOUTH, game->textures[SOUTH].path);
    init_mlx_wall_texture(game, WEST, game->textures[WEST].path);
    init_mlx_wall_texture(game, EAST, game->textures[EAST].path);

	set_colors(game, game->color, CEILING);
	set_colors(game, game->color, FLOOR);
    // Set up rendering and input handling
	mlx_hook(game->win, KeyPress, KeyPressMask, press_key, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, release_key, game);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_rotate, game);
    mlx_hook(game->win, DestroyNotify, ButtonPressMask, &close_window, game);
    mlx_hook(game->win, 17, 0, &close_window, game);
    mlx_loop_hook(game->mlx, &render, game);

    // ✅ This should be the last function call
    mlx_loop(game->mlx);
}

