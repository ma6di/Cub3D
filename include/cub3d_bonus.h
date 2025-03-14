#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>
# include <stdarg.h>
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define TILE_SIZE 32

# define FOV_FACTOR 0.66

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define LIGHTBLUE 0xD8D8FF
# define LIGHTRED	0xFFBBCF
# define RESET "\033[0m"

# define BUFFER			1024
# define SCREEN_WIDTH	800
# define SCREEN_HEIGHT	600
# define MOVE_SPEED		0.04
# define ROTATE_SPEED	0.05

# define NORTH	0
# define SOUTH	1
# define WEST	2
# define EAST	3
# define DOOR	4

# define FLOOR	0
# define CEILING	1

# define FORWARD 1
# define BACKWARD 2
# define LEFT 3
# define RIGHT 4
# define LEFT_ROTATE 5
# define RIGHT_ROTATE 6

# define KEY_W 0
# define KEY_A 1
# define KEY_S 2
# define KEY_D 3
# define KEY_RIGHT 4
# define KEY_LEFT 5
# define KEY_SPACE 6

# define PUSH 1
# define POP 0

typedef struct s_stack
{
	int	*x;
	int	*y;
	int	top;
	int	size;
}				t_stack;

typedef struct s_texture_params
{
	int		tex_x;
	double	step;
	double	tex_pos;
}			t_texture_params;

typedef struct s_tile_coords
{
	int		x;
	int		y;
	double	tile_x;
	double	tile_y;
}				t_tile_coords;

/* 🎨 Colors */
typedef struct s_color
{
	char	*col_tex_str;	// color string
	char	*img;
	char	*addr;
	int		r;
	int		g;
	int		b;
	int		hex_color;
	int		mode; //1:color   2:texture
	int	 	width;	  // Image width
	int	 	height;	 // Image height
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
}			t_color;

/* 📌 Textures */
typedef struct s_texture
{
	char	*path;
	void	*img;	   // Pointer to MiniLibX image
	char	*addr;	  // Image data address
	int	 	width;	  // Image width
	int	 	height;	 // Image height
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
	int		door_state;
	int		**door_pos;
}			t_texture;

/* 🚶 Player */
typedef struct s_player
{
	char 	*ini_dir;
	double  x;		  // Player's X position
	double  y;		  // Player's Y position
	double  dir_x;	  // Direction vector X
	double  dir_y;	  // Direction vector Y
	double  plane_x;	// Camera plane X (for FOV)
	double  plane_y;	// Camera plane Y (for FOV)
} t_player;

typedef struct s_minimap
{
    int tile_size;
    int offset_x;
    int offset_y;
}       t_minimap;

typedef struct	s_ray
{
	double	camera_x;
	double	dirx; //ray direction
	double	diry;
	int		mapx;	//current map cell
	int		mapy;
	double	side_distx; //distance to next side
	double	side_disty;
	double	deltadistx; //distance between sides
	double	deltadisty;
	double	walldist; //distance to wall
	int		stepx;	//step direction
	int		stepy;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		door;
}				t_ray;
/* 🎮 Game Structure */

typedef struct s_game
{
	int				map_statred;
	int				file_order;
	int				bpp;		// Bits per pixel
	int				line_len;   // Bytes per line
	int				endian;	 // Endian format
	char			**map;			  // 2D array for the map
	int				width;			   // Map width
	int				height;
	void			*mlx;				// MiniLibX connection
	void			*win;				// Window pointer
	void			*img;
	void			*addr;
	int				keys[6];
	t_player		player;			  // Player data
	t_texture	  	textures[5];		 // Textures: [0]NO, [1]SO, [2]EA, [3]WE
	t_color			color[2];
	t_minimap		minimap;	 // Floor RGB color
	t_ray		ray;
}				t_game;

int		validate_file(const char *filename);
int		pars_file(const char *filename, t_game *game, char** argv);
int		validate_cub_elements(t_game *game);
int		is_valid_texture_path(char *path);
int		validate_colors(t_color *color);
int		is_valid_color_texture(t_color *color);
int		is_map_closed_and_accessible(t_game *game, char **map, \
			int height, int width);
void	free_two_dim(char **arr);
int		two_dim_len(char **arr);
void	cal_map_dim(t_game **game);
int		free_game(t_game *game);
void	print_error(const char *format, ...);
void	create_window(t_game *game);
void	init_game(t_game *game);
int		press_key(int keycode, t_game *game);
int		close_window(t_game *game);
void	move_player(int keycode, t_game *game);
void	cast_rays(t_game *game);
int		render(t_game *game);
void	init_win(t_game *game);
int		case_one(t_game *game, char **map, int y, int height);
int		case_two(t_game *game, char **map, int y, int height);
int		case_three(t_game *game, char **map, int x, int height);
int		case_four(t_game *game, char **map, int x, int height);
int		case_five(t_game *game, char **map, int x, int height);
int		first_pos_row(char *line);
int		last_pos_row(char *line);
int		first_pos_col(char **map, int col);
int		last_pos_col(char **map, int col, int height);
void	init_mlx_ray(t_ray *ray, t_game *game, int x);
void	print_struct(t_game *game);
void	calculate_wall_height(t_ray *ray, t_game *game);
void	perform_dda(t_ray *ray, t_game *game);
void	calculate_step(t_ray *ray, t_game *game);
void	load_player(t_game *game);
void	set_dir(t_game *game);
void	init_mlx_wall_texture(t_game *game, int index, char *path);
void	init_mlx_fc_texture(t_game *game, int index, char *path);
int		select_texture(t_ray *ray, t_game *game);
void	rotate_player(int direction, t_game *game);
void	move_player(int direction, t_game *game);
int		rgb_to_hex(int r, int g, int b);
void	set_colors(t_game *game, t_color *color, int index);
void	draw_floor_and_ceiling(t_game *game, int index);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
int		get_cf_texture_pixel(t_color *color, int x, int y, int tex_id);
int		mouse_rotate(int x, int y, t_game *game);
void	minimap(t_game *game);
int		release_key(int keycode, t_game *game);
void	update_player(t_game *game);
void	init_ray(t_ray *ray);
void	draw_ceiling_row(t_game *game, int y, double step_x, double step_y);
void	draw_floor_row(t_game *game, int y, double step_x, double step_y);
bool	is_empty_line(const char *line);
void	remove_trailing_empty_lines(char **map);
int		check_empty_line(char **map);
void	flood_fill(t_game *game, int **visited);
void	free_visited(int **visited, int height);
int		check_accessibility(t_game *game, int **visited);
void	free_stack(t_stack *stack);
t_stack	*init_stack(int size);
void	init_directions(int *dxy);
int		check_enclosure(t_game *game, char **map);
int		validate_map_chars(t_game *game);
int		check_corners(t_game *game, char **map);



#endif
