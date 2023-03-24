# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2023/03/24 16:56:28 by tdubois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS		:=	--no-print-directory

.DELETE_ON_ERROR:
.SECONDEXPANSION:

#==============================================================================#
#=== GOALS ====================================================================#

NAME		:=	minirt

#==============================================================================#
#=== DIRECTORIES ==============================================================#

SRC			:=	srcs
BUILD		:=	.build

INCLUDES	:=	-Iincludes -Ilib/libft -I/usr/include -Ilib/mlx42/include

#==============================================================================#
#=== COMPILATION ==============================================================#

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -Wno-unused-function -Ofast
CPPFLAGS	:=	-MP -MMD $(INCLUDES)
LDFLAGS		:=	-Llib/libft -lft			\
				-Llib/mlx42/build -lmlx42	\
				-ldl -lglfw -pthread -lm	\

ifdef DEBUG
	CFLAGS += -ggdb3
endif

#==============================================================================#
#=== SOURCES ==================================================================#

SRCS	:=	$(shell find $(SRC) -name '*.c')

#==============================================================================#
#=== BUILD FILES ==============================================================#

OBJS	:=	$(SRCS:$(SRC)/%.c=$(BUILD)/%.o)
DEPS	:=	$(SRCS:$(SRC)/%.c=$(BUILD)/%.d)
DIRS	:=	$(sort $(shell dirname $(OBJS)))

#==============================================================================#
#=== COLORS ===================================================================#

NOC			:=	\033[0m
RED			:=	\e[1m\e[38;5;196m
GREEN		:=	\e[1m\e[38;5;76m
BLUE		:=	\e[1m\e[38;5;33m
PURPLE		:=	\033[1;35m

#==============================================================================#
#=== PROGRESS BAR UTILS =======================================================#

NB_COMPIL			:=	0
ifndef	RECURSIVE
TOTAL_COMPIL		:=	$(shell expr $$(make -n RECURSIVE=1 | grep clang | wc -l) - 1)
endif
ifndef TOTAL_COMPIL
TOTAL_COMPIL		:=	$(words $(OBJS))
endif

#******************************************************************************#
#*** PHONY RULES **************************************************************#

.PHONY:	all				\
		libft libmlx42	\
		clean fclean re	\

all: libft libmlx42 $(NAME)

libft:
	$(MAKE) -C lib/libft

libmlx42:
	cmake lib/mlx42 -B lib/mlx42/build						\
		&& cmake --build lib/mlx42/build -j$(nproc) -- -s

clean:
	@echo -e "$(RED)Deleting objects$(NOC)"
	@rm -rf $(BUILD)
	@$(MAKE) -C lib/libft clean
	@cmake --build lib/mlx42/build --target clean -- -s

fclean: clean
	@echo -e "$(RED)Deleting binary$(NOC)"
	@rm -rf $(NAME)
	@$(MAKE) -C libft fclean
	@rm -rf lib/mlx42/build

re : fclean all

#******************************************************************************#
#*** BUILD RULES **************************************************************#

$(NAME) : $(OBJS)
	@echo -e "$(BLUE)Creation of binary$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	@echo -e "$(GREEN)Done$(NOC)"

$(DIRS):
	@mkdir -p $@

$(OBJS): $(BUILD)/%.o : $(SRC)/%.c | $$(@D)
	$(if $(filter $(NB_COMPIL),0), @echo -e "$(BLUE)Compiling$(NOC)")
	$(eval NB_COMPIL=$(shell expr $(NB_COMPIL) + 1))
	@echo -e "[$(NB_COMPIL)/$(TOTAL_COMPIL)] $(PURPLE)Compiling $< $(NOC)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)
