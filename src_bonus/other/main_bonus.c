#include "cub3d_bonus.h"

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
