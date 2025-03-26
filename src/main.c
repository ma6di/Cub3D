

#include "cub3D.h"

int	render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_floor_and_ceiling(game, FLOOR);
	cast_rays(game);
	update_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc != 2)
		return (print_error("Error: Please provide a map file\n"), 1);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		print_error("Error: Memory allocation failed\n");
		return (1);
	}
	init_game(game);
	if (!pars_file(argv[1], game, argv))
	{
		print_struct(game);
		close_window(game);
		return (1);
	}
	create_window(game);
	close_window(game);
	return (0);
}
