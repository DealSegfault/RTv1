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
				create_ocl.c \
				frame.c \
				hooks.c \
				main.c \
				parser.c \
				ray.c \
				raytrace.c \
				set_ocl.c \
				supersampler.c \
				filters.c \
				copyrt.c \
				create_complex.c \
				thread.c \
				intersect/cone.c \
				intersect/cone2.c \
				intersect/cylinder.c \
				intersect/sphere.c \
				intersect/plane.c \
				xml/xml_parser.c \
				xml/xml_errors.c \
				xml/xml_checks.c \
				gtk/gtk_init.c 	\
				gtk/gtk_new.c 	\
				gtk/gtk_launcher.c \
				gtk/gtk_settings.c \
				gtk/gtk_callback.c \

MINILIBX	=	libs/minilibx/libmlx.a
LIBFT		=	libs/libft/libft.a
LIBVEC		=	libs/libvec/libvec.a
LIBXML		=	-lxml2
OBJ			=	$(addprefix $(OBJDIR),$(SRC:.c=.o))
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I includes/ -I libs/libft/includes/ -I libs/libvec/includes/ -I libs/libxml/ `pkg-config --cflags gtk+-3.0` -g
OPTI		=	-O3
DEBUG		=	-g
MLXF		=	-framework OpenGL -framework AppKit `pkg-config --libs gtk+-3.0`

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
	@$(CC) $(CFLAGS) -o $@ -c $<

mlx:
	@printf "$(YELLOW)[MINILIBX] Compiling obj...                                                     \r$(NO_COLOR)"
	@make -s -C libs/minilibx 2> /dev/null > /dev/null

lib:
	@make -s -C libs/libft 2> /dev/null > /dev/null

vec:
	@make -s -C libs/libvec 2> /dev/null > /dev/null

$(OBJDIR):
	@mkdir $(OBJDIR)
	@mkdir $(OBJDIR)/gtk
	@mkdir $(OBJDIR)/intersect
	@mkdir $(OBJDIR)/xml

clean:
	@make -s -C libs/libft clean
	@make -s -C libs/libvec clean
	@printf "$(YELLOW)[$(PROJECT)] Removing obj..."
	@rm -rf $(OBJ)
	@rm -rf $(OBJDIR)
	@printf "\r$(GREEN)[$(PROJECT)] Obj removed.                                                   \n$(NO_COLOR)"

fclean:
	@make -s -C libs/minilibx clean
	@make -s -C libs/libft fclean
	@make -s -C libs/libvec fclean
	@printf "$(YELLOW)[$(PROJECT)] Removing obj..."
	@rm -rf $(OBJ)
	@rm -rf $(OBJDIR)
	@printf "\r$(GREEN)[$(PROJECT)] Obj removed.                                                   \n$(NO_COLOR)"
	@printf "$(YELLOW)[$(PROJECT)] Removing $(NAME)..."
	@rm -rf $(NAME)
	@printf "\r$(GREEN)[$(PROJECT)] $(NAME) removed.                                               \n$(NO_COLOR)"

re: fclean all

.PHONY: all clean fclean re
