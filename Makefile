# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/23 19:29:24 by mparigi           #+#    #+#              #
#    Updated: 2017/09/29 00:41:08 by ocojeda-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT		=	RT
NAME		=	rt
OBJDIR		=	objs/
SRCDIR		=	srcs/
SRC			=	color.c \
				init/create_ocl.c \
				init/create_complex.c \
				frame.c \
				main.c \
				parser.c \
				ray.c \
				raytrace.c \
				set_ocl.c \
				filters.c \
				filters2.c \
				copyrt.c \
				thread.c \
				matrix.c \
				debug.c \
				hooks.c \
				hooks2.c \
				reflexion.c \
				refraction.c \
				intersect/limits.c \
				intersect/plane.c \
				intersect/cylinder.c \
				intersect/sphere.c \
				intersect/cone.c \
				intersect/intersect.c \
				intersect/intensity.c \
				xml/xml_parser.c \
				xml/xml_errors.c \
				xml/xml_checks.c \
				checker.c \
				uv_mapping.c \
				perlin.c
				# gtk/gtk_btn.c	\
				# gtk/gtk_init.c \
				# gtk/gtk_launcher.c \
				# gtk/gtk_settings.c \
				# gtk/gtk_new.c

MINILIBX	=	libs/minilibx/libmlx.a
LIBFT		=	libs/libft/libft.a
LIBVEC		=	libs/libvec/libvec.a
LIBXML		=	-lxml2
OBJ			=	$(addprefix $(OBJDIR),$(SRC:.c=.o))
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I includes/ -I libs/libft/includes/ -I libs/libvec/includes/ -I libs/libxml/ -g #`pkg-config --cflags gtk+-3.0`
OPTI		=	
DEBUG		=	-g
MLXF		=	-framework OpenGL -framework AppKit -lxml2 #`pkg-config --libs gtk+-3.0`
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
	@$(CC) $(OPTI) $(CFLAGS) -o $@ -c $<

mlx:
	@printf "$(YELLOW)[MINILIBX] Compiling obj...                                                     \r$(NO_COLOR)"
	@make -s -C libs/minilibx 2> /dev/null > /dev/null

lib:
	@make -s -C libs/libft 2> /dev/null > /dev/null

vec:
	@make -s -C libs/libvec 2> /dev/null > /dev/null

$(OBJDIR):
	@mkdir $(OBJDIR)
	@mkdir $(OBJDIR)gtk
	@mkdir $(OBJDIR)intersect
	@mkdir $(OBJDIR)xml
	@mkdir $(OBJDIR)init

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
