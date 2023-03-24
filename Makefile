# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2023/03/24 18:39:13 by tdubois          ###   ########.fr        #
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

#******************************************************************************#
#*** PHONY RULES **************************************************************#

.PHONY:	all				\
		libft libmlx42	\
		clean fclean re	\

all: libft libmlx42 $(NAME)

libft:
	@$(MAKE) -C lib/libft

libmlx42:
	@cmake lib/mlx42 -B lib/mlx42/build						\
		&& cmake --build lib/mlx42/build -j$(nproc) -- -s

clean:
	@$(MAKE) -C lib/libft clean
	@cmake --build lib/mlx42/build --target clean -- -s
	@$(info $(RED)Deleting objects$(NOC))
	@rm -rf $(BUILD)

fclean: clean
	@$(MAKE) -C lib/libft fclean
	@rm -rf lib/mlx42/build
	@$(info $(RED)Deleting binary$(NOC))
	@rm -rf $(NAME)

re: TOTAL_COMPIL = $(words $(OBJS))
re: fclean all

#******************************************************************************#
#*** BUILD RULES **************************************************************#

$(NAME): $(OBJS)
	@$(info $(BLUE)Linking C executable $@$(NOC))
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	@$(info $(GREEN)Done$(NOC))

$(DIRS):
	@mkdir -p $@

$(OBJS): $(BUILD)/%.o: $(SRC)/%.c | $$(@D)
	$(progress-bar)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%% COLORS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

NOC			:=	$(shell echo "\033[0m")
RED			:=	$(shell echo "\e[1m\e[38;5;196m")
GREEN		:=	$(shell echo "\e[1m\e[38;5;76m")
BLUE		:=	$(shell echo "\e[1m\e[38;5;33m")
PURPLE		:=	$(shell echo "\033[1;35m")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%% PROGRESS BAR UTILS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

NB_COMPIL	:=	0

ifndef REC
TOTAL_COMPIL := $(shell make REC=1 -n $(OBJS) | grep clang | wc -l)
endif

define progress-bar =
	$(eval NB_COMPIL=$(shell expr $(NB_COMPIL) + 1))
	$(info [$(NB_COMPIL)/$(TOTAL_COMPIL)] $(PURPLE)Building $< $(NOC))
endef
