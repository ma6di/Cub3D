
#include "../../include/cub3d_bonus.h"

void	check_ammo_paths(t_game *game, int start, int end, t_ammo *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!game->ammo[i].path)
		{
			print_error(RED"Error: cub file data is not in order\n"RESET);
			game->file_order = 1;
		}
		i++;
	}
}

void	check_c_ammo_paths(t_game *game, int start, int end, \
			t_c_ammo_tex *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!game->c_ammo_tex[i].path)
		{
			print_error(RED"Error: cub file data is not in order\n"RESET);
			game->file_order = 1;
		}
		i++;
	}
}

void	check_heart_paths(t_game *game, int start, int end, t_heart_tex *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!game->heart_tex[i].path)
		{
			print_error(RED"Error: cub file data is not in order\n"RESET);
			game->file_order = 1;
		}
		i++;
	}
}

void	check_health_paths(t_game *game, int start, int end, t_health *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!game->health_bar[i].path)
		{
			print_error(RED"Error: cub file data is not in order\n"RESET);
			game->file_order = 1;
		}
		i++;
	}
}

void	check_key_paths(t_game *game, int start, int end, t_key_tex *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!game->key_tex[i].path)
		{
			print_error(RED"Error: cub file data is not in order\n"RESET);
			game->file_order = 1;
		}
		i++;
	}
}
