#include "cub3d.h"

static int	stack_op(t_stack *stack, int *x, int *y, int op)
{
	if (op == PUSH && stack->top + 1 < stack->size)
	{
		stack->top++;
		stack->x[stack->top] = *x;
		stack->y[stack->top] = *y;
		return (1);
	}
	if (op == POP && stack->top >= 0)
	{
		*x = stack->x[stack->top];
		*y = stack->y[stack->top];
		stack->top--;
		return (1);
	}
	return (0);
}

static int	is_valid(t_game *game, int **visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->width || y >= game->height)
		return (0);
	if (!visited[y] || !game->map[y])
		return (0);
	if (visited[y][x] || (game->map[y][x] && game->map[y][x] == '1' ))
		return (0);
	return (1);
}

static void	process_flood_fill(t_game *game, int **visited, \
								t_stack *stack, int *dxy)
{
	int	x;
	int	y;
	int	nx;
	int	ny;
	int	i;

	init_directions(dxy);
	while (stack_op(stack, &x, &y, POP))
	{
		if (!is_valid(game, visited, x, y))
			continue ;
		visited[y][x] = 1;
		i = 0;
		while (i < 8)
		{
			nx = x + dxy[i];
			ny = y + dxy[i + 1];
			if (ny < game->height && nx < (int)ft_strlen(game->map[ny]))
			{
				if (is_valid(game, visited, nx, ny))
					stack_op(stack, &nx, &ny, PUSH);
			}
			i += 2;
		}
	}
}

void	flood_fill(t_game *game, int **visited)
{
	t_stack	*stack;
	int		x;
	int		y;
	int		dxy[8];

	stack = init_stack(game->width * game->height);
	if (!stack)
		return ;
	x = game->player.x;
	y = game->player.y;
	stack_op(stack, &x, &y, PUSH);
	process_flood_fill(game, visited, stack, dxy);
	free_stack(stack);
}
