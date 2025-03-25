
# Source files
#SRCS    = src/render_ceiling_and_floor.c src/free_destroy_game.c  \
             src/render_walls.c src/initilisation.c src/set_game_data.c  \
             src/Key_handler.c src/tools.c src/main.c src/validate_colors.c \
             src/map_corner_cases.c src/validate_elements.c src/parse_file.c \
             src/movement.c src/validate_map.c src/validate_texture_path.c \
             src/print_error.c src/window.c src/rays.c src/initilisation2.c \
			 src/debug.c src/map_empty_line_check.c \
			 src/map_enclosement_check.c src/map_check_tools.c src/map_accessibility_check.c \
			 src/flood_fill.c src/flood_fill_tool.c src/map_char_check.c


#BONUS_SRCS = src_bonus/ammo_bar/ammo_bar_bonus.c \
             src_bonus/collectibe_heart/collectibe_heart_tools_bonus.c \
             src_bonus/collectibe_heart/collectible_hear_set_bonus.c \
             src_bonus/collectibe_heart/collectible_heart_render_bonus.c \
             src_bonus/collectible_ammo/collectible_ammo_render_bonus.c \
             src_bonus/collectible_ammo/collectible_ammo_set_bonus.c \
             src_bonus/collectible_ammo/collectible_ammo_tools_bonus.c \
             src_bonus/collectible_key/collectibe_key_set_bonus.c \
             src_bonus/collectible_key/collectible_key_render_bonus.c \
             src_bonus/collectible_key/collectible_key_tools_bonus.c \
             src_bonus/door/door_tools_bonus.c \
             src_bonus/door/set_doors_data_bonus.c \
             src_bonus/door/update_door_state_bonus.c \
             src_bonus/free_game/free_destroy_game_bonus.c \
             src_bonus/free_game/free_mlx_bonus.c \
             src_bonus/free_game/free_tex_path_bonus.c \
             src_bonus/gun/gun_bonus.c \
             src_bonus/gun/shooting_effect_bonus.c \
             src_bonus/health_bar/health_bar_bonus.c \
             src_bonus/init/init_c_ammo_heart_key_bonus.c \
             src_bonus/init/init_game_payer_minimap_colors_bonus.c \
             src_bonus/init/init_gun_ray_health_ammo_bar_bonus.c \
             src_bonus/init/init_textures_bonus.c \
             src_bonus/keyboard_and_mouse/Key_handler_bonus.c \
             src_bonus/map_checks/flood_fill_bonus.c \
             src_bonus/map_checks/flood_fill_tool_bonus.c \
             src_bonus/map_checks/map_accessibility_check_bonus.c \
             src_bonus/map_checks/map_char_check_bonus.c \
             src_bonus/map_checks/map_check_tools_bonus.c \
             src_bonus/map_checks/map_corner_cases_bonus.c \
             src_bonus/map_checks/map_empty_line_check_bonus.c \
             src_bonus/map_checks/map_enclosement_check_bonus.c \
             src_bonus/map_checks/validate_map_bonus.c \
             src_bonus/map_checks/validate_map_bonus.c \
             src_bonus/map_checks/validate_texture_path_bonus.c \
             src_bonus/minimap/draw_mini_player_view_angel_bonus.c \
             src_bonus/minimap/minimap_bonus.c \
             src_bonus/movement/movement_bonus.c \
             src_bonus/parsing/check_tex_path_bonus.c \
             src_bonus/parsing/parse_file_bonus.c \
             src_bonus/parsing/parse_line1_bonus.c \
             src_bonus/parsing/parse_line2_bonus.c \
             src_bonus/ray_casting/door_dda_bonus.c \
             src_bonus/ray_casting/rays_bonus.c \
             src_bonus/ray_casting/render_walls_bonus.c \
             src_bonus/render_order_bonus/render_order_bonus.c \
             src_bonus/render_order_bonus/store_objects_in_array_bonus.c \
             src_bonus/set_game_data/set_game_data_bonus.c \
             src_bonus/set_game_data/set_mlx_tex_bonus.c \
             src_bonus/sky_and_floor/render_ceiling_and_floor_bonus.c \
             src_bonus/sky_and_floor/render_ceiling_bonus.c \
             src_bonus/sky_and_floor/render_floor_bonus.c \
             src_bonus/sky_and_floor/render_sky_bonus.c \
             src_bonus/sky_and_floor/validate_colors_bonus.c \
             src_bonus/sprite/kill_sprite_bonus.c \
             src_bonus/sprite/move_sprite_bonus.c \
             src_bonus/sprite/render_sprite_bonus.c \
             src_bonus/sprite/set_sprites_bonus.c \
             src_bonus/print_error_bonus.c \
             src_bonus/window_bonus.c \
             src_bonus/debug_bonus.c

CC      = gcc -g
# Directories
SRCDIR  = src
BONUSDIR = src_bonus
OBJDIR  = obj
INCDIR  = include
MLXDIR  = minilibx
LIBFTDIR = libft

# Libraries
LIBFT    = $(LIBFTDIR)/libft.a
MLX      = $(MLXDIR)/libmlx.a
MLX_FLAGS = -L$(MLXDIR) -lmlx -lXext -lX11 -lXrender -lm
LIBFT_INC = -I$(LIBFTDIR)/include
MLX_INC  = -I$(MLXDIR)

# Source Files
SRCS := $(wildcard $(SRCDIR)/**/*.c)
BONUS_SRCS := $(wildcard $(BONUSDIR)/**/*.c)

# Object Files (Flattened)
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BONUS_OBJS := $(patsubst $(BONUSDIR)/%.c, $(OBJDIR)/%.o, $(BONUS_SRCS))

# Output program names
NAME = cub3D
BONUS_NAME = cub3D_bonus

# Rules
all: $(LIBFT) $(MLX) $(NAME)

bonus: $(LIBFT) $(MLX) $(BONUS_NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(MLX):
	@chmod +x $(MLXDIR)/configure
	@$(MAKE) -C $(MLXDIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(BONUS_NAME)

# Compilation rule (creates obj/ if needed)
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)  # Ensures the directory exists
	$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFT_INC) $(MLX_INC) -c $< -o $@

$(OBJDIR)/%.o: $(BONUSDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)  # Ensures the directory exists
	$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFT_INC) $(MLX_INC) -c $< -o $@

# Ensure obj/ exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(MAKE) -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
