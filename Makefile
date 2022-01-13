# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2022/01/13 12:07:59 by fmonbeig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -MMD -I$(HEADER_DIR)
LIB_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm libft/libft.a #TODO check if minilibx flags are working, and modify it if needed
LIB_PATH = libft/.

SRCS_DIR = .

SRCS = 	main.c\
		error_and_free.c\
		check_file.c\
		check_map.c\
		get_element.c\
		get_map.c\
		get_colour.c\
		check_map2.c

#TODO Ajouter sub_folders ex : $(SUB_SRCS_ARCHITECTURE) puis ajouter
#TODO (suite ex) SUB_SRCS_ARCHITECTURE = 				\
#TODO (suite ex) main.c ...

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

vpath %.c #TODO ajouter path folders ex ./architecture
vpath %.h . ./libft
