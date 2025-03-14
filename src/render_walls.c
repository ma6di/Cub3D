#include "cub3D.h"

/**
 * get_texture_pixel - Retrieves the color of a pixel from the texture.
 * @texture: Pointer to the texture structure.
 * @x: X coordinate on the texture.
 * @y: Y coordinate on the texture.
 *
 * Returns: The color of the pixel at the specified coordinates in the texture.
 * The function get_texture_pixel() is designed to extract the pixel color from 
 * a texture based on the x and y coordinates, and a given texture ID (tex_id). 
 * It takes a texture array, x, and y values as input and returns the pixel color as an integer.
 */
int get_wall_texture_pixel(t_texture *texture, int x, int y, int tex_id)
{
    if (!texture || tex_id < 0 || tex_id >= 5)  // ✅ Ensure valid texture index
    {
        print_error("Error: Invalid texture ID %d\n", tex_id);
        return -1;
    }

    if (!texture[tex_id].addr)
    {
        press_key("Error: texture[%d].addr is NULL\n", tex_id);
        return -1;
    }

    if (x < 0 || x >= texture[tex_id].width || y < 0 || y >= texture[tex_id].height)
    {
        print_error("Error: Invalid coordinates x=%d, y=%d for texture[%d] (width=%d, height=%d)\n",
                x, y, tex_id, texture[tex_id].width, texture[tex_id].height);
        return -1;
    }

    char *dst = texture[tex_id].addr + (y * texture[tex_id].line_len + x * (texture[tex_id].bpp / 8));

    int color = 0;
    memcpy(&color, dst, sizeof(int));  // ✅ Safe memory read
    return color;
}


/**
 * my_mlx_pixel_put - Puts a pixel with a specified color at the given screen coordinates.
 * 
 * This function writes a pixel at the specified screen position `(x, y)` in the texture
 * buffer used for rendering the screen. The function performs boundary checks, ensures
 * the texture image buffer is correctly initialized, checks the line length, and then writes
 * the color to the calculated pixel location. If any error occurs, the function will print
 * an error message and exit without modifying the image.
 *
 * @game: Pointer to the game structure containing texture data.
 * @x: The x-coordinate of the pixel to be modified.
 * @y: The y-coordinate of the pixel to be modified.
 * @color: The color (in RGBA format) to write to the pixel.
 */
void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    // ✅ Ensure pixel is within screen bounds
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    {
        print_error("Error: Pixel (%d, %d) out of bounds!\n", x, y);
        return;
    }

    // ✅ Ensure image buffer is valid
    if (!game->img || !game->addr)
    {
        print_error("Error: Image buffer is not initialized!\n");
        return;
    }

    // ✅ Write the color to the image buffer
    char *dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int *)dst = color;
}


/**
 * render_wall_slice - Draws a vertical slice of a wall with textures
 * @game: Pointer to the game structure
 * @ray: Pointer to the ray structure
 * @x: The current screen column being drawn
 * @tex_id: The texture index to use
 *
 * This function retrieves texture data and draws a vertical slice of a
 * wall on the screen based on raycasting calculations.
 */
static void render_wall_slice(t_game *game, t_ray *ray, int x, int tex_id)
{
    int y;
    int tex_x;
    int tex_y;
    int color;
    double tex_pos;
    double step;

    // ✅ Correct wall_x calculation
	double wall_x;
	if (ray->side == 0)  // Vertical wall (East/West)
		wall_x = game->player.y + ray->walldist * ray->diry;
	else                 // Horizontal wall (North/South)
		wall_x = game->player.x + ray->walldist * ray->dirx;

	// ✅ Use the wall's grid position to keep textures fixed on the wall
	wall_x -= floor(wall_x);

    // ✅ Ensure tex_x stays within bounds
    tex_x = (int)(wall_x * game->textures[tex_id].width);
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= game->textures[tex_id].width) tex_x = game->textures[tex_id].width - 1;

    // ✅ Calculate texture step size for vertical scaling
    step = (double)game->textures[tex_id].height / ray->lineheight;
    tex_pos = (ray->drawstart - SCREEN_HEIGHT / 2 + ray->lineheight / 2) * step;

    for (y = ray->drawstart; y < ray->drawend; y++)
    {
        if (y < 0 || y >= SCREEN_HEIGHT)  // Extra safety check
            continue;

        tex_y = (int)fmod(tex_pos, game->textures[tex_id].height);
        tex_pos += step;

        // ✅ Get pixel color from texture
        color = get_wall_texture_pixel(game->textures, tex_x, tex_y, tex_id);

        // ✅ Properly darken walls based on side
        if (ray->side == 1) 
        {
            int r = (color & 0xFF0000) >> 16;
            int g = (color & 0x00FF00) >> 8;
            int b = (color & 0x0000FF);

            r /= 2;
            g /= 2;
            b /= 2;

            color = (r << 16) | (g << 8) | b;
        }

        my_mlx_pixel_put(game, x, y, color);
    }
}


/**
 * cast_rays - Main raycasting function to render the scene
 * @game: Pointer to the game structure
 *
 * This function loops through all screen columns, casting a ray per column,
 * computing intersections with walls, and rendering the correct wall slices.
 * 
 * Loop Through Each Vertical Screen Column → Each column represents a ray.
	Initialize Ray (t_ray) → Calculate its direction based on the player’s position.
	Use DDA Algorithm to Find Wall Hits → Step through the grid to detect where the ray collides with a wall.
	Compute Distance to Wall → Needed for scaling wall height.
	Draw the Wall Strip → Convert the 3D projection into vertical lines on the screen.

 */
void cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;
	int		y;
	int		color;
	init_ray(&ray);
	// Loop through each column (X-coordinate)
	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		// Initialize the ray for this column
		init_mlx_ray(&ray, game, x);
		calculate_step(&ray, game);
		perform_dda(&ray, game);
		calculate_wall_height(&ray, game);
        int tex_id = select_texture(&ray, game);
        render_wall_slice(game, &ray, x, tex_id);
	}
}
