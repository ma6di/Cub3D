/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_select_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:58:24 by mcheragh          #+#    #+#             */
/*   Updated: 2025/04/02 13:42:20 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// static int	g_map_selected = 0;

int	cleanup_start_page(t_start_page *start_page, int free_map)
{
	if (free_map && start_page->selected_map)
		free(start_page->selected_map);
	if (start_page->win)
		mlx_destroy_window(start_page->mlx, start_page->win);
	if (start_page->mlx && start_page->img)
		mlx_destroy_image(start_page->mlx, start_page->img);
	if (start_page->mlx && start_page->addr)
		mlx_destroy_image(start_page->mlx, start_page->addr);
	if (start_page->mlx)
	{
	#ifndef __APPLE__
		mlx_destroy_display(start_page->mlx);
	#endif
		free(start_page->mlx);
	}
	if (free_map)
		free(start_page);
	return (0);
}

int	handle_keypresses(int keycode, t_start_page *start_page)
{
	#ifdef __APPLE__
		if (keycode == 18) // key '1'
			start_page->selected_map = strdup("maps_bonus/level1.cub");
		else if (keycode == 19) // key '2'
			start_page->selected_map = strdup("maps_bonus/level2.cub");
		else if (keycode == 53) // Escape key
		{
			cleanup_start_page(start_page, 1);
			exit(0);
		}
	#elif __linux__
		if (keycode == 49 || keycode == 65436)
			start_page->selected_map = strdup("maps_bonus/level1.cub");
		else if (keycode == 50 || keycode == 65433)
			start_page->selected_map = strdup("maps_bonus/level2.cub");
		else if (keycode == 65307)
		{
			cleanup_start_page(start_page, 1);
			exit(0);
		}
	#endif
	if (start_page->selected_map)
	{
		mlx_destroy_window(start_page->mlx, start_page->win);
		open_game(start_page->selected_map, start_page);
	}
	return (0);
}

void	display_starting_page(t_start_page *start_page, char *start_img)
{
	if (!start_img)
	{
		print_error(RED"Error: No image to display on the starting page\n"RESET);
		return ;
	}
	mlx_put_image_to_window(start_page->mlx, start_page->win, start_img, 0, 0);
	mlx_string_put(start_page->mlx, start_page->win, 450, 400, 0xFFFFFF, "Select a Map:");
	mlx_string_put(start_page->mlx, start_page->win, 450, 450, 0xFFFFFF, "1. Office Map");
	mlx_string_put(start_page->mlx, start_page->win, 450, 500, 0xFFFFFF, "2. Maze Map");
}

static int	init_start_page(t_start_page *start_page)
{
	if (!start_page->mlx)
	{
		print_error(RED"Error: Failed to initialize MiniLibX\n"RESET);
		return (0);
	}
	start_page->win = mlx_new_window(start_page->mlx, 1000, 600, "Cub3D - Select Map");
	if (!start_page->win)
	{
		print_error(RED"Error: Failed to create window\n"RESET);
		cleanup_start_page(start_page, 1);
		return (0);
	}
	start_page->img = mlx_new_image(start_page->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	start_page->addr = mlx_xpm_file_to_image(start_page->mlx,
		"assets/start_page.xpm", &start_page->width, &start_page->height);
	if (!start_page->addr)
	{
		print_error(RED"Error: Failed to load start page image\n"RESET);
		cleanup_start_page(start_page, 1);
		return (0);
	}
	return (1);
}

void	start(t_start_page *start_page)
{
	start_page->width = 1000;
	start_page->height = 600;
	start_page->selected_map = NULL;
	start_page->mlx = mlx_init();
	if (!init_start_page(start_page))
		cleanup_start_page(start_page, 1);
	display_starting_page(start_page, start_page->addr);
	mlx_hook(start_page->win, 2, 1L << 0, handle_keypresses, start_page);
	//mlx_loop_hook(start_page->mlx, mlx_loop_hook_break, start_page);
	mlx_loop(start_page->mlx);
	cleanup_start_page(start_page, 0);
	return;
}
