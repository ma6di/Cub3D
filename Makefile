# Compiler and Flags
CC      = gcc -g
CFLAGS  =

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

# Source files
SRCS    = src/render_ceiling_and_floor.c src/free_destroy_game.c  \
             src/render_walls.c src/initilisation.c src/set_game_data.c  \
             src/Key_handler.c src/tools.c src/main.c src/validate_colors.c \
             src/map_corner_cases.c src/validate_elements.c src/parse_file.c \
             src/movement.c src/validate_map.c src/validate_texture_path.c \
             src/print_error.c src/window.c src/rays.c src/initilisation2.c \
			 src/debug.c src/map_empty_line_check.c \
			 src/map_enclosement_check.c src/map_check_tools.c src/map_accessibility_check.c \
			 src/flood_fill.c src/flood_fill_tool.c src/map_char_check.c


BONUS_SRCS = src_bonus/render_ceiling_and_floor_bonus.c src_bonus/free_destroy_game_bonus.c src_bonus/set_doors_data_bonus.c \
             src_bonus/render_walls_bonus.c src_bonus/initilisation_bonus.c src_bonus/set_game_data_bonus.c  src_bonus/sprite_bonus.c\
             src_bonus/Key_handler_bonus.c src_bonus/tools_bonus.c src_bonus/main_bonus.c src_bonus/validate_colors_bonus.c \
             src_bonus/map_corner_cases_bonus.c src_bonus/validate_elements_bonus.c src_bonus/minimap_bonus.c src_bonus/parse_file_bonus.c \
             src_bonus/movement_bonus.c src_bonus/validate_map_bonus.c src_bonus/validate_texture_path_bonus.c src_bonus/gun_bonus.c \
             src_bonus/print_error_bonus.c src_bonus/window_bonus.c src_bonus/rays_bonus.c src_bonus/initilisation2_bonus.c \
			 src_bonus/render_ceiling_bonus.c src_bonus/render_floor_bonus.c src_bonus/debug_bonus.c src_bonus/map_empty_line_check_bonus.c \
			 src_bonus/map_enclosement_check_bonus.c src_bonus/map_check_tools_bonus.c src_bonus/map_accessibility_check_bonus.c \
			 src_bonus/flood_fill_bonus.c src_bonus/flood_fill_tool_bonus.c src_bonus/map_char_check_bonus.c src_bonus/render_sky_bonus.c \
			 src_bonus/health_bar_bonus.c src_bonus/armor_bar_bonus.c src_bonus/collectible_heart_bonus.c

OBJS    = $(SRCS:src/%.c=$(OBJDIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:src_bonus/%.c=$(OBJDIR)/%.o)

# Output program name
NAME    = cub3D
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

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFT_INC) $(MLX_INC) -c $< -o $@

$(OBJDIR)/%.o: $(BONUSDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFT_INC) $(MLX_INC) -c $< -o $@

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
