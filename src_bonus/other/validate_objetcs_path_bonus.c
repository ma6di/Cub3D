#include "cub3d_bonus.h"

int	validate_ammo_paths(int start, int end, t_ammo *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!is_valid_texture_path_b(assets[i].path))
			return (0);
		i++;
	}
	return (1);
}

int	validate_c_ammo_paths(int start, int end, \
			t_c_ammo_tex *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!is_valid_texture_path_b(assets[i].path))
			return (0);
		i++;
	}
	return (1);
}

int	validate_heart_paths(int start, int end, t_heart_tex *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!is_valid_texture_path_b(assets[i].path))
			return (0);
		i++;
	}
	return (1);
}

int	validate_health_paths(int start, int end, t_health *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!is_valid_texture_path_b(assets[i].path))
			return (0);
		i++;
	}
	return (1);
}

int	validate_key_paths(int start, int end, t_key_tex *assets)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!is_valid_texture_path_b(assets[i].path))
			return (0);
		i++;
	}
	return (1);
}
