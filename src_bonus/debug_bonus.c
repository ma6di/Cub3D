#include "cub3d_bonus.h"

//prints the data parsed from the .cub file
void print_struct(t_game *game)
{
	int i = 0;
	int j = 0;
	printf("Textures:::\n---------------------------- \n");
	printf("NO %s\n", game->textures[NORTH].path);
	printf("SO %s\n", game->textures[SOUTH].path);
	printf("WE %s\n", game->textures[WEST].path);
	printf("EA %s\n", game->textures[EAST].path);
	printf("D %s\n", game->textures[DOOR].path);
	printf("\n\nFloor and Ceiling Color:::\n---------------------------- \n");
	if(game->color[FLOOR].mode == 1)
	{
		printf("floor color r: %d\n", game->color[FLOOR].r);
		printf("floor color g: %d\n", game->color[FLOOR].g);
		printf("floor color b: %d\n", game->color[FLOOR].b);
	}
	else if(game->color[FLOOR].mode == 2)
		printf("floor texture: %s\n", game->color[FLOOR].col_tex_str);
	if(game->color[CEILING].mode == 1)
	{
		printf("ceiling color r: %d\n", game->color[CEILING].r);
		printf("ceiling color g: %d\n", game->color[CEILING].g);
		printf("ceiling color b: %d\n", game->color[CEILING].b);
	}
	else if(game->color[CEILING].mode == 2)
		printf("ceiling texture: %s\n", game->color[CEILING].col_tex_str);
	printf("\n\nPlayer Position:::\n---------------------------- \n");
	printf("player x: %f\n", game->player.x);
	printf("player y: %f\n", game->height - game->player.y - 1);
	printf("player direction: %s\n", game->player.ini_dir);
	printf("\n\nGame Width and Height:::\n---------------------------- \n");
	printf("Game max width: %d\n", game->width);
	printf("Game height: %d\n", game->height);
	printf("\n\nMAP:::\n---------------------------- \n");
	while (game->map[i] && i < game->height)
	{
		// Print Y-coordinates in green
		printf(GREEN);
		if (game->height - i - 1 <= 9)
			printf("%d ", game->height - i - 1);
		else
			printf("%d", game->height - i - 1);
		printf(RESET); // Reset color

		j = 0;
		while (game->map[i][j])
		{
			printf(" %c ", game->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	// Print X-coordinates in red
	printf(GREEN"^\n");
	printf(RED " > 0  " RESET);

	i = 1;
	j = 0;
	while (j < game->width)
	{
		if (i > 9)
			i = 0;
		printf(RED "%d  " RESET, i);
		i++;
		j++;
	}
	printf("\n\n");
}