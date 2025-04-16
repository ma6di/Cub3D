# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 11:54:34 by mcheragh          #+#    #+#              #
#    Updated: 2025/04/07 17:38:40 by mcheragh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = libft.a
SRC_DIR     = ./
OBJ_DIR     = obj/
CC          = cc -fPIC
CFLAGS      =  -g
INCLUDE     = -I include
AR          = ar rcs
RM          = rm -f
GREEN       = \033[0;32m
RESET       = \033[0m

SRC_FILES = \
	ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint \
	ft_itoa ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_putchar_fd \
	ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strchr ft_strdup \
	ft_striteri ft_strjoin ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
	ft_strnstr ft_strrchr ft_strtrim ft_substr ft_tolower ft_toupper \
	ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus ft_lstlast_bonus \
	ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus \
	ft_printf ft_print_idsc ft_print_ptr ft_print_unsigned ft_print_hex \
	get_next_line_utils get_next_line print_error

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# Rules
all: building_message $(NAME)
	@echo "$(GREEN)Libft built ✅$(RESET)"

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

building_message:
	@echo "$(GREEN)Compiling Libft...$(RESET)"

clean:
	@$(RM) -rf $(OBJ_DIR)

fclean: clean
	@$(RM) -f $(NAME)
	@echo "$(GREEN)Libft cleaned ✅$(RESET)"

re: fclean all

.PHONY: all clean fclean re
