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
# define SCREEN_WIDTH	1000
# define SCREEN_HEIGHT	600
# define MOVE_SPEED		0.04
# define ROTATE_SPEED	0.005

# define NORTH	0
# define SOUTH	1
# define WEST	2
# define EAST	3
# define DOOR	4
# define ZOMBIE 5

# define FLOOR	0
# define CEILING	1
# define SKY	2

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
# define KEY_CTRL 7

# define GUN 0
# define GUN_SHUT 1


# define PUSH 1
# define POP 0


#define SAFE_DISTANCE 0.5


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
}			t_texture;


/* 🚶 Player */
typedef struct s_door
{
	int	x;		  // Door's X position
	int	y;		  // Door's Y position
	int	door_state; // 0 (close), 1, 2, 3, 4, 5(open)
} t_door;

typedef struct s_sprite
{
    double x;   // Sprite world X position
    double y;   // Sprite world Y position
    double distance;  // Distance from player (for sorting)
    int visible;  // If the sprite is visible in the player's view
    double speed;     // ✅ Speed of movement
    int active;       // ✅ 1 = moving, 0 = idle
	int    health;
} t_sprite;


/* 🚶 Player */
typedef struct s_player
{
	char 	*ini_dir;
	double  x;		  // Player's X position
	double  y;		  // Player's Y position
	double  dir_x;	  // Direction vector X
	double  dir_y;	  // Direction vector Y
	double  plane_x;	// Camera plane X _b(for FOV)
	double  plane_y;	// Camera plane Y (for FOV)
	int		health;
	int		ammo;
	int		key;
} t_player;

typedef struct s_minimap
{
    int tile_size;
    int offset_x;
    int offset_y;
}       t_minimap;

typedef struct s_gun
{
    int screen_x;
    int screen_y;
	int height;
    int width;
	char	*path;
	void	*img;	   // Pointer to MiniLibX image
	char	*addr;	  // Image data address
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
}       t_gun;

typedef struct s_ammo
{
    int screen_x;
    int screen_y;
	int height;
    int width;
	char	*path;
	void	*img;	   // Pointer to MiniLibX image
	char	*addr;	  // Image data address
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
}       t_ammo;

typedef struct s_heath
{
    int screen_x;
    int screen_y;
	int height;
    int width;
	char	*path;
	void	*img;	   // Pointer to MiniLibX image
	char	*addr;	  // Image data address
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
}       t_health;

typedef struct s_heart_tex
{
    int screen_x;
    int screen_y;
	int height;
    int width;
	char	*path;
	void	*img;	   // Pointer to MiniLibX image
	char	*addr;	  // Image data address
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
}       t_heart_tex;

typedef struct s_heart
{
    double x;          // World X position
    double y;          // World Y position
    double distance;   // Distance from player
    int visible;       // 1 = visible, 0 = not visible
    int active;        // 1 = exists, 0 = collected
    int animation_index;  // 🔄 Current frame of animation (0-11)
    int animation_timer;  // ⏳ Counts frames to control animation speed
} t_heart;

typedef struct s_c_ammo
{
    double x;          // World X position
    double y;          // World Y position
    double distance;   // Distance from player
    int visible;       // 1 = visible, 0 = not visible
    int active;        // 1 = exists, 0 = collected
    int animation_index;  // 🔄 Current frame of animation (0-11)
    int animation_timer;  // ⏳ Counts frames to control animation speed
} t_c_ammo;

typedef struct s_c_ammo_tex
{
    int screen_x;
    int screen_y;
	int height;
    int width;
	char	*path;
	void	*img;	   // Pointer to MiniLibX image
	char	*addr;	  // Image data address
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
}       t_c_ammo_tex;

typedef struct s_ckey
{
    double x;          // World X position
    double y;          // World Y position
    double distance;   // Distance from player
    int visible;       // 1 = visible, 0 = not visible
    int active;        // 1 = exists, 0 = collected
    int animation_index;  // 🔄 Current frame of animation (0-11)
    int animation_timer;  // ⏳ Counts frames to control animation speed
} t_key;

typedef struct s_key_tex
{
    int screen_x;
    int screen_y;
	int height;
    int width;
	char	*path;
	void	*img;	   // Pointer to MiniLibX image
	char	*addr;	  // Image data address
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
}       t_key_tex;

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
	int		zombie;
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
	int				door_count;
	int				sprite_count;
	int				heart_count;
	int				c_ammo_count;
	int				key_count;
	void			*mlx;				// MiniLibX connection
	void			*win;				// Window pointer
	void			*img;
	void			*addr;
	int				keys[7];
	t_player		player;			  // Player data
	t_texture	  	textures[6];		 // Textures: [0]NO, [1]SO, [2]EA, [3]WE
	t_color			color[3];
	t_minimap		minimap;
	t_door			*door;	 // Floor RGB color
	t_ray			ray;
	t_gun			gun[2];
	t_sprite		*sprites;
	double			*z_buffer;
	t_health		health_bar[5];
	t_ammo			ammo[7];
	t_heart			*heart;
	t_heart_tex		heart_tex[12];
	t_c_ammo		*c_ammo;
	t_c_ammo_tex	c_ammo_tex[12];
	t_key			*key;
	t_key_tex		key_tex[7];
}				t_game;

int		validate_file_b(const char *filename);
int		pars_file_b(const char *filename, t_game *game, char** argv);
int		validate_cub_elements_b(t_game *game);
int		is_valid_texture_path_b(char *path);
int		validate_colors_b(t_color *color);
int		is_valid_color_texture_b(t_color *color);
int		is_map_closed_and_accessible_b(t_game *game, char **map, \
			int height, int width);
void	free_two_dim_b(char **arr);
int		two_dim_len_b(char **arr);
void	cal_map_dim_b(t_game **game);
int		free_game_b(t_game *game);
void	print_error_b(const char *format, ...);
void	create_window_b(t_game *game);
void	init_game_b(t_game *game);
int		press_key_b(int keycode, t_game *game);
int		close_window_b(t_game *game);
void	move_player_b(int keycode, t_game *game);
void	cast_rays_b(t_game *game);
int		render_b(t_game *game);
void	init_win_b(t_game *game);
int		case_one_b(t_game *game, char **map, int y, int height);
int		case_two_b(t_game *game, char **map, int y, int height);
int		case_three_b(t_game *game, char **map, int x, int height);
int		case_four_b(t_game *game, char **map, int x, int height);
int		case_five_b(t_game *game, char **map, int x, int height);
int		first_pos_row_b(char *line);
int		last_pos_row_b(char *line);
int		first_pos_col_b(char **map, int col);
int		last_pos_col_b(char **map, int col, int height);
void	init_mlx_ray_b(t_ray *ray, t_game *game, int x);
void	print_struct_b(t_game *game);
void	calculate_wall_height_b(t_ray *ray, t_game *game, int x);
void	perform_dda_b(t_ray *ray, t_game *game);
void	calculate_step_b(t_ray *ray, t_game *game);
void	load_player_b(t_game *game);
void	set_dir_b(t_game *game);
void	init_mlx_wall_texture_b(t_game *game, int index, char *path);
void	init_mlx_fc_texture_b(t_game *game, int index, char *path);
int		select_texture_b(t_ray *ray, t_game *game);
void	rotate_player_b(int direction, t_game *game);
void	move_player_b(int direction, t_game *game);
int		rgb_to_hex_b(int r, int g, int b);
void	set_colors_b(t_game *game, t_color *color, int index);
void	draw_floor_and_ceiling_b(t_game *game, int index);
void	my_mlx_pixel_put_b(t_game *game, int x, int y, int color);
int		get_cf_texture_pixel_b(t_color *color, int x, int y, int tex_id);
int		mouse_rotate_b(int x, int y, t_game *game);
void	minimap_b(t_game *game);
int		release_key_b(int keycode, t_game *game);
void	update_player_b(t_game *game);
void	init_ray_b(t_ray *ray);
bool	is_empty_line_b(const char *line);
void	remove_trailing_empty_lines_b(char **map);
int		check_empty_line_b(char **map);
void	flood_fill_b(t_game *game, int **visited);
void	free_visited_b(int **visited, int height);
int		check_accessibility_b(t_game *game, int **visited);
void	free_stack_b(t_stack *stack);
t_stack	*init_stack_b(int size);
void	init_directions_b(int *dxy);
int		check_enclosure_b(t_game *game, char **map);
int		validate_map_chars_b(t_game *game);
int		check_corners_b(t_game *game, char **map);
int		check_walls_b(t_game *game, char **map);
void	draw_floor_texture_b(t_game *game);
void	draw_floor_pixel_b(t_game *game);
void	draw_ceiling_texture_b(t_game *game);
void	draw_ceiling_pixel_b(t_game *game);
void	draw_sky_texture_b(t_game *game);
void	set_doors(t_game *game);
int		is_door_b(t_game *game);
int		which_door(t_game *game, double world_y, double world_x);
void	draw_gun_b(t_game *game);
void	init_gun_b(t_gun *gun, int dim, int index);
void	init_mlx_gun_texture_b(t_game *game, int index, char *path);
void	render_gun_shut_b(t_game *game);
void render_sprites(t_game *game, t_sprite *sprites);
void	set_sprites(t_game *game);
void	set_sprites_cords(t_game *game);
void	move_sprites(t_game *game);
void	ft_player_health_b(t_game *game);
t_sprite *get_zombie_in_front(t_game *game);
void	remove_zombie(t_game *game, int index);
void	init_health_bar_b(t_health *health_bar, int width, int height);
void	render_health_bar_b(t_game *game);
void	init_mlx_health_bar_texture_b(t_game *game);
void	render_ammo_bar_b(t_game *game);
void	init_mlx_ammo_bar_texture_b(t_game *game);
void	init_ammo_b(t_ammo *ammo, int width, int height);
void render_hearts(t_game *game, t_heart *heart);
void	set_heart_cords(t_game *game);
void	check_collect_hearts(t_game *game);
void	init_mlx_heart_texture_b(t_game *game);
void	init_heart_tex_b(t_heart_tex *heart_tex, int dim);
void	init_c_ammo_tex_b(t_c_ammo_tex *c_ammo_tex, int dim);
void	init_mlx_c_ammo_texture_b(t_game *game);
void	set_c_ammo_cords(t_game *game);
void	render_c_ammo(t_game *game, t_c_ammo *c_ammo);
void	check_collect_ammo(t_game *game);
void	init_key_tex_b(t_key_tex *key_tex, int width, int height);
void	init_mlx_key_texture_b(t_game *game);
void	set_key_cords(t_game *game);
void render_key(t_game *game, t_key *key);
void	check_collect_key(t_game *game);
int		is_zombie_near(t_game *game, double new_x, double new_y);
int		is_player_near(t_game *game, double new_x, double new_y);

#endif
