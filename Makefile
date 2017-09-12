# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/26 19:16:02 by bbeldame          #+#    #+#              #
#    Updated: 2017/08/14 22:04:16 by rlecart          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT		=	RT
NAME		=	rt
OBJDIR		=	objs/
SRCDIR		=	srcs/
SRC			=	color.c \
				cone.c \
				create_ocl.c \
				cylinder.c \
				frame.c \
				hooks.c \
				main.c \
				parser.c \
				plane.c \
				ray.c \
				raytrace.c \
				set_ocl.c \
				sphere.c \
				supersampler.c \
				filters.c \
				cone2.c \
				copyrt.c \
				thread.c \
				xml_parser.c \
				xml_errors.c \
				xml_checks.c \

MINILIBX	=	minilibx_macos/libmlx.a
LIBFT		=	libft/libft.a
LIBVEC		=	libvec/libvec.a
LIBXML		=	-lxml2
OBJ			=	$(addprefix $(OBJDIR),$(SRC:.c=.o))
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I includes/ -I libft/includes/ -I libvec/includes/ -I /usr/include/libxml2
OPTI		=	-O3
DEBUG		=	-g
MLXF		=	-framework OpenGL -framework AppKit

WHITE		=	\033[7;49;39m
BLUE		=	\033[7;49;34m
RED			=	\x1B[31m
YELLOW		=	\x1B[33m
GREEN		=	\033[0;49;32m
GREEN_BG	=	\033[1;49;32m
GRAY		=	\033[7;49;90m
NO_COLOR	=	\033[m

all: mlx lib vec $(NAME)

$(NAME): $(MINILIBX) $(LIBFT) $(GRAPHICS) $(OBJDIR) $(OBJ)
	@printf "\r$(GREEN)[$(PROJECT)] Obj compilation done.                                                        \n"
	@printf "$(YELLOW)[$(PROJECT)] Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(DEBUG) $(MLXF) -o $(NAME) $(OBJ) $(MINILIBX) $(LIBFT) $(LIBVEC) $(LIBXML)
	@printf "\r$(GREEN)[$(PROJECT)] Compilation done.                          \n$(NO_COLOR)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@printf "$(YELLOW)\r[$(PROJECT)] Compiling $< to $@                                                          \r"
	@$(CC) $(CFLAGS) -g -o $@ -c $<

mlx:
	@printf "$(YELLOW)[MINILIBX] Compiling obj...                                                     \r$(NO_COLOR)"
	@make -s -C minilibx_macos 2> /dev/null > /dev/null

lib:
	@make -s -C libft 2> /dev/null > /dev/null

vec:
	@make -s -C libvec 2> /dev/null > /dev/null

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@make -s -C libft clean
	@make -s -C libvec clean
	@printf "$(YELLOW)[$(PROJECT)] Removing obj..."
	@rm -rf $(OBJ)
	@rm -rf $(OBJDIR)
	@printf "\r$(GREEN)[$(PROJECT)] Obj removed.                                                   \n$(NO_COLOR)"

fclean:
	@make -s -C minilibx_macos clean
	@make -s -C libft fclean
	@make -s -C libvec fclean
	@printf "$(YELLOW)[$(PROJECT)] Removing obj..."
	@rm -rf $(OBJ)
	@rm -rf $(OBJDIR)
	@printf "\r$(GREEN)[$(PROJECT)] Obj removed.                                                   \n$(NO_COLOR)"
	@printf "$(YELLOW)[$(PROJECT)] Removing $(NAME)..."
	@rm -rf $(NAME)
	@printf "\r$(GREEN)[$(PROJECT)] $(NAME) removed.                                               \n$(NO_COLOR)"

re: fclean all

.PHONY: all clean fclean re
