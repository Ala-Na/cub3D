# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anadege <anadege@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2022/01/14 22:48:23 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -MMD -I$(HEADER_DIR)
LIB_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm libft/libft.a
LIB_PATH = libft/.

SRCS_DIR = .

SRCS = 	main.c \
		print.c\
		$(SUB_SRCS_HOOKS) \
		$(SUB_SRCS_RENDERING) \
		$(SUB_SRCS_ERROR_FREE) \
		$(SUB_SRCS_PARSING_CHECKS) \
		$(SUB_SRCS_PARSING_GETS)

SUB_SRCS_HOOKS =	hooks.c \
					rotations.c \
					shifts.c

SUB_SRCS_RENDERING =	image_manip.c \
						launching.c \
						raycast_dda.c \
						raycast_textures.c
					
SUB_SRCS_ERROR_FREE =	errors.c \
						free_memory.c

SUB_SRCS_PARSING_CHECKS =	check_file.c \
							check_map.c \
							check_map2.c

SUB_SRCS_PARSING_GETS =	get_colour_utils.c \
						get_colour.c \
						get_element.c \
						get_map_info.c \
						init_img.c \
						malloc_map.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = .objs

HEADER_DIR = .

PREREQ = 	$(OBJS:%.o=%.d)

MAKE = make
MAKE_DIR = mkdir -p
MAKE_RM = rm -f

all: libft.a $(NAME)

$(NAME):	$(OBJS) libft/libft.a
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_FLAGS)

-include $(PREREQ)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
			$(CC) -I$(LIB_PATH) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
			$(MAKE_DIR) $@

libft.a:
			$(MAKE) -C libft

clean:
			$(MAKE_RM) -r $(OBJS_DIR)

fclean: 	clean
			$(MAKE_RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re

vpath %.c ./hooks ./rendering ./error_free ./parsing_checks ./parsing_gets
vpath %.h . ./libft ./minilibx-linux
