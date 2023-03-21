# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2023/03/21 14:06:53 by aderouba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS		:=	--no-print-directory
.DEFAULT_GOAL	:=	all
.DELETE_ON_ERROR:
.SECONDEXPANSION:
SHELL			:= bash
.SHELLFLAGS		:= -c

#=================================COMPILATION==================================#
CC			:=	clang
INCLUDES	:=	-Iincludes -Ilibft -I/usr/include -IMLX42/include
LIBFLAGS	:=	-LMLX42/build -lmlx42 -ldl -lglfw -pthread -lm
LIBFTFLAGS	:=	-Llibft -lft
CFLAGS		:=	-MP -MMD -Wall -Wextra -Werror $(INCLUDES) -Wno-unused-function -Ofast

#==================================EXECUTABLE==================================#
NAME	:=	minirt
BUILD	:=	.build

#=================================SOURCE FILES=================================#
SRCS	:=	srcs/main.c							\
			srcs/objects/plane.c				\
			srcs/objects/camera.c				\
			srcs/objects/sphere.c				\
			srcs/objects/cylinder.c				\
			srcs/objects/space_operations.c		\
			srcs/image/draw.c					\
			srcs/utils/rtlst.c					\
			srcs/utils/print.c					\
			srcs/utils/vector.c					\
			srcs/utils/number.c					\
			srcs/utils/string.c					\
			srcs/utils/math_utils.c				\
			srcs/utils/parse_utils.c			\
			srcs/parsing/parse_file.c			\
			srcs/parsing/parse_lights.c			\
			srcs/parsing/parse_objects.c

#====================================OBJECTS===================================#
OBJS	:=	${SRCS:srcs/%.c=$(BUILD)/%.o}
DEPS	:=	$(SRCS:srcs/%.c=$(BUILD)/%.d)
DIRS	:=	$(sort $(shell dirname $(OBJS)))

#====================================COLORS====================================#
NOC			:=	\033[0m
RED			:=	\e[1m\e[38;5;196m
GREEN		:=	\e[1m\e[38;5;76m
BLUE		:=	\e[1m\e[38;5;33m
PURPLE		:=	\033[1;35m

#================================PROGRESS BAR UTILS============================#
NB_COMPIL			:=	0
ifndef	RECURSIVE
TOTAL_COMPIL		:=	$(shell expr $$(make -n RECURSIVE=1 | grep clang | wc -l) - 1)
endif
ifndef TOTAL_COMPIL
TOTAL_COMPIL		:=	$(words $(OBJS))
endif

#=====================================RULES====================================#
$(DIRS):
	@mkdir -p $@

$(BUILD)/%.o : srcs/%.c | $$(@D)
	$(if $(filter $(NB_COMPIL),0), @echo -e "$(BLUE)Compiling$(NOC)")
	$(eval NB_COMPIL=$(shell expr $(NB_COMPIL) + 1))
	@echo -e "[$(NB_COMPIL)/$(TOTAL_COMPIL)] $(PURPLE)Compiling $< $(NOC)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	@make -C libft
	@cd MLX42 && cmake -DBUILD_TESTS=ON -B build && cmake --build build --parallel
	@make -sC MLX42/build
	@echo -e "$(BLUE)Creation of binary$(NOC)"
	@$(CC) $(CFLAGS) $^ $(LIBFLAGS) $(LIBFTFLAGS) -o $@
	@echo -e "$(GREEN)Done$(NOC)"

all : $(NAME)

clean :
	@echo -e "$(RED)Deleting objects$(NOC)"
	@rm -rf $(DIRS)
	@make clean -C libft
	@rm -rf MLX42/build

fclean : clean
	@echo -e "$(RED)Deleting binary$(NOC)"
	@rm -f $(NAME)
	@make fclean -C libft

re :
	@make fclean
	@make $(NAME) RECURSIVE=1 TOTAL_COMPIL=$(words $(OBJS))

norm:
	@echo -ne "$(RED)"
	@{ ! norminette includes srcs libft | grep Error; } && echo -e "$(GREEN)All normed !";
	@echo -ne "$(NOC)"

.PHONY: all clean fclean re norm

-include $(DEPS)
