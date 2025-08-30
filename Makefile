# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/25 16:22:18 by mpico-bu          #+#    #+#              #
#    Updated: 2025/07/25 16:22:18 by mpico-bu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = cub3D
LIBFT = ./libft/libft.a
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm


SRC = 	src/main.c \
		src/map_reader.c \
		src/map_textures.c \
		src/map_validate.c \
		src/draw_and_render/draw.c \
		src/draw_and_render/player.c \
		src/draw_and_render/raycasting.c \
		src/draw_and_render/rendering.c \
		src/draw_and_render/utils.c

OBJDIR = obj
OBJS = $(SRC:src/%.c=$(OBJDIR)/%.o)
RM = rm -rf

all: $(OBJDIR) $(LIBFT) $(MLX_LIB) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) -Llibft -lft

$(LIBFT):
	@make -C libft

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@$(RM) $(OBJDIR)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all re clean fclean
