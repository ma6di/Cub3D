
#include "cub3D.h"


int	free_game(t_game *game)
{
	free_mlx(game);
	if(game->textures[NORTH].addr)
		mlx_destroy_image(game->mlx, game->textures[NORTH].addr);
	if(game->textures[SOUTH].addr)
		mlx_destroy_image(game->mlx, game->textures[SOUTH].addr);
	if(game->textures[WEST].addr)
		mlx_destroy_image(game->mlx, game->textures[WEST].addr);
	if(game->textures[EAST].addr)
		mlx_destroy_image(game->mlx, game->textures[EAST].addr);
	if(game->win)
		mlx_destroy_window(game->mlx, game->win);
	if(game->mlx)
		mlx_destroy_display(game->mlx);
	if(game->mlx)
		free(game->mlx);
	if(game->map)
		free_two_dim(game->map);
	if(game->textures[NORTH].addr)
		free(game->textures[NORTH].addr);
	if(game->textures[SOUTH].addr)
		free(game->textures[SOUTH].addr);
	if(game->textures[WEST].addr)
		free(game->textures[WEST].addr);
	if(game->textures[EAST].addr)
		free(game->textures[EAST].addr);
	if(game->color[FLOOR].col_tex_str)
		free(game->color[FLOOR].col_tex_str);
	if(game->color[CEILING].col_tex_str)
		free(game->color[CEILING].col_tex_str);
	free(game);
	exit (EXIT_FAILURE);
}

int close_window(t_game *game)
{
    // Destroy the game window if it exists
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);

    // Free textures if they exist
    for (int i = 0; i < 5; i++) 
    {
        if (game->textures[i].img)
            mlx_destroy_image(game->mlx, game->textures[i].img);
    }

    // Free map memory if allocated
    if (game->map)
    {
        for (int i = 0; game->map[i]; i++)
            free(game->map[i]); // Free each row of the map
        free(game->map); // Free the map itself
    }

    // Destroy the MLX instance
    mlx_destroy_display(game->mlx);
    free(game->mlx); // Free the MLX pointer

    exit(0);
}