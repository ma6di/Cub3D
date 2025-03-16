

#include "cub3d_bonus.h"

int	render_b(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_floor_and_ceiling_b(game, CEILING);
	draw_floor_and_ceiling_b(game, FLOOR);
	cast_rays_b(game);
	minimap_b(game);
	update_player_b(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
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
