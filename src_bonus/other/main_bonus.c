#include "cub3d_bonus.h"

int handle_keypresses(int keycode, t_start_page *start_page)
{
    printf("Key pressed: %d\n", keycode); // Print the keycode to the terminal

    if (keycode == 49 || keycode == 65436) // Keycode for '1'
    {
        start_page->selected_map = strdup("maps_bonus/level1.cub");
        printf("Map selected: %s\n", start_page->selected_map); // Debug: Print the selected map
    }
    else if (keycode == 50 || keycode == 65433) // Keycode for '2'
    {
        start_page->selected_map = strdup("maps_bonus/level2.cub");
        printf("Map selected: %s\n", start_page->selected_map); // Debug: Print the selected map
    }
    else if (keycode == 65307) // Escape key to exit
    {
        exit(0); // Exit the program
    }

    if (start_page->selected_map != NULL)
    {
        // Exit the MiniLibX loop
        mlx_loop_end(start_page->mlx);
    }

    return (0); // Continue the loop
}

void display_starting_page(t_start_page *start_page, char *start_img)
{
    if (!start_img)
    {
        print_error(RED"Error: No image to display on the starting page\n"RESET);
        return;
    }

    // Load and display the starting page image
    mlx_put_image_to_window(start_page->mlx, start_page->win, start_img, 0, 0);

    // Display map selection options
    mlx_string_put(start_page->mlx, start_page->win, 50, 100, 0xFFFFFF, "Select a Map:");
    mlx_string_put(start_page->mlx, start_page->win, 50, 150, 0xFFFFFF, "1. Office Map");
    mlx_string_put(start_page->mlx, start_page->win, 50, 200, 0xFFFFFF, "2. Maze Map");
}

void start(t_start_page *start_page)
{
    // Create a temporary window for the starting page
    start_page->mlx = mlx_init();
    start_page->win = mlx_new_window(start_page->mlx, 1000, 600, "Cub3D - Select Map");
    if (!start_page->win)
    {
        print_error(RED"Error: Failed to create window\n"RESET);
        exit(1);
    }
    start_page->width = 1000;
    start_page->height = 600;
    start_page->selected_map = NULL;

    // Load the starting page image
    start_page->img = mlx_new_image(start_page->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    start_page->addr = mlx_xpm_file_to_image(start_page->mlx, "assets/start_page.xpm", &start_page->width, &start_page->height);

    if (!start_page->addr)
    {
        print_error(RED"Error: Failed to load start page image\n"RESET);
        mlx_destroy_window(start_page->mlx, start_page->win);
        exit(1);
    }

    // Display the starting page and wait for user input
    display_starting_page(start_page, start_page->addr);
    mlx_hook(start_page->win, KeyPress, KeyPressMask, handle_keypresses, start_page);

    // Start the MiniLibX event loop
    mlx_loop(start_page->mlx);

    // Free resources after the loop ends
    if (start_page->win)
    {
        mlx_destroy_window(start_page->mlx, start_page->win);
        start_page->win = NULL;
    }
    if (start_page->mlx && start_page->img)
    {
        mlx_destroy_image(start_page->mlx, start_page->img);
        start_page->img = NULL;
    }
    if (start_page->mlx)
    {
        mlx_destroy_display(start_page->mlx);
        free(start_page->mlx);
        start_page->mlx = NULL;
    }
}

int	open_game(char * selected_map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		print_error(RED"Error: Memory allocation failed\n"RESET);
		return (1);
	}
    game->mlx = mlx_init();
	printf("mlx init\n");
	init_game_b(game);
	if (!pars_file_b(selected_map, game))
	{
		print_struct_b(game);
		close_window_b(game);
		return (1);
	}
	print_struct_b(game);
	create_window_b(game);
	close_window_b(game);
	return (0);
}

int main(void)
{
	t_start_page *start_page;

	start_page = ft_calloc(1, sizeof(t_start_page));
    if (!start_page)
    {
        print_error(RED"Error: Memory allocation failed\n"RESET);
        return (1);
    }

    // Initialize MiniLibX and display the starting page
	start(start_page);
    // Start the event loop
    //mlx_loop_hook(game->mlx, game_loop, game); // Hook to check for map selection
   // mlx_loop(game->mlx);
   printf("start_page->selected_map is: %s\n", start_page->selected_map);
	open_game(start_page->selected_map);
    return (0);
}

void	game_over(void)
{
	printf("\033[1;31m");
	printf("   ██████  █████  ███    ███ ███████     \n");
	printf("  ██      ██   ██ ████  ████ ██          \n");
	printf("  ██      ███████ ██ ████ ██ █████       \n");
	printf("  ██   ██ ██   ██ ██  ██  ██ ██          \n");
	printf("   ██████ ██   ██ ██      ██ ███████     \n");
	printf("                                         \n");
	printf("    ████   ██     ██ ███████ █████       \n");
	printf("  ██    ██ ██     ██ ██      ██  ██      \n");
	printf("  ██    ██ ██     ██ █████   ██████      \n");
	printf("  ██    ██  ██   ██  ██      ██  █       \n");
	printf("    ████     █████   ███████ ██   █      \n");
	printf("\033[0m\n");
}

void	victory(void)
{
	printf(GREEN"");
	printf("\\ \\    / /|_ _||  __||_____| / _ \\ |  _ \\\\  // \n");
	printf(" \\ \\  / /  | | | |     | |  | | | || |_) \\\\V/  \n");
	printf("  \\  V /   | | | |___  | |  | |_| ||  _ < ||   \n");
	printf("   \\__/   |___ \\____|  |_|   \\___/ |_| |_\\||   \n");
	printf(RESET"");
}