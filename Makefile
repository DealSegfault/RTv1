# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/23 19:29:24 by mparigi           #+#    #+#              #
#    Updated: 2017/10/02 00:13:22 by mparigi          ###   ########.fr        #
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
				ray.c \
				raytrace.c \
				filters.c \
				filters2.c \
				copyrt.c \
				thread.c \
				thread2.c \
				matrix.c \
				debug.c \
				hooks.c \
				hooks2.c \
				hooks3.c \
				hooks4.c \
				reflexion.c \
				refraction.c \
				intersect/limits.c \
				intersect/plane.c \
				intersect/cylinder.c \
				intersect/sphere.c \
				intersect/cone.c \
				intersect/intersect.c \
				intersect/intensity.c \
				uv_mapping.c \
				gtk/gtk_add.c \
				gtk/gtk_add2.c \
				gtk/gtk_init.c \
				gtk/gtk_launcher.c \
				gtk/gtk_settings.c \
				gtk/gtk_new.c \
				checker.c \
				xml/xml_get_nodes.c \
				xml/xml_parser.c \
				xml/xml_errors.c \
				xml/xml_checks.c \
				xml/xml_skibox.c \
				xml/xml_parse_nodes.c \
				xml/xml_parse_light.c \
				xml/xml_parse_obj.c \
				xml/xml_parse_negs.c

MINILIBX	=	libs/minilibx/libmlx.a
LIBFT		=	libs/libft/libft.a
LIBVEC		=	libs/libvec/libvec.a
LIBXML		=	`xml2-config --libs`
LIBXML_H	=	`xml2-config --cflags`
LIB_GTK		=	`pkg-config --libs gtk+-3.0`
LIB_GTK_H	=	`pkg-config --cflags gtk+-3.0`
DEBUG		=	-g -fsanitize=address
OBJ			=	$(addprefix $(OBJDIR),$(SRC:.c=.o))
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra $(DEBUG) -I includes/ -I libs/libft/includes/ -I libs/libvec/includes/ $(LIBXML_H) $(LIB_GTK_H)
OPTI		=	
MLXF		=	-framework OpenGL -framework AppKit -lxml2
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
	@$(CC) $(CFLAGS) $(DEBUG) $(MLXF) -o $(NAME) $(OBJ) $(MINILIBX) $(LIBFT) $(LIBVEC) $(LIBXML) $(LIB_GTK)
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
