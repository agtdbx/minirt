# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .unit.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2023/03/31 12:21:47 by tdubois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%% CONFIGURATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

MAKEFLAGS		:=	--no-print-directory

.POSIX:
.SILENT:
.DELETE_ON_ERROR:
.SECONDEXPANSION:

#==============================================================================#
#=== GOALS ====================================================================#

NAME		:=	unit

LIBMLX42	:=	lib/mlx42/build/libmlx42.a
LIBFT		:=	lib/libft/unit.a

#==============================================================================#
#=== DIRECTORIES ==============================================================#

SRC			:=	srcs
BUILD		:=	.build-unit

INCLUDES	:=	-Iincludes -Ilib/libft -I/usr/include -Ilib/mlx42/include \
				-Itests

#==============================================================================#
#=== COMPILATION ==============================================================#

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -Wno-unused-function -ggdb3
CPPFLAGS	:=	-MP -MMD $(INCLUDES)
LDFLAGS		:=	-Llib/libft -l:unit.a		\
				-Llib/mlx42/build -lmlx42	\
				-ldl -lglfw -pthread -lm	\

#==============================================================================#
#=== SOURCES ==================================================================#

#TODO
SRCS	:=	$(shell fd -g '*.c' -E 'main.c' $(SRC))

TESTS	:=	$(shell fd -g '*.test.c' $(SRC) $(dir $(LIBFT)))

#==============================================================================#
#=== BUILD FILES ==============================================================#

MAIN	:=	$(BUILD)/main.gen.c
MAINOBJ	:=	$(BUILD)/main.gen.o

OBJS	:=	$(SRCS:$(SRC)/%.c=$(BUILD)/%.o)
DEPS	:=	$(SRCS:$(SRC)/%.c=$(BUILD)/%.d)
DIRS	:=	$(sort $(shell dirname $(OBJS)))

#******************************************************************************#
#*** PHONY RULES **************************************************************#

.PHONY:	all				\
		libft objs		\
		clean fclean re	\

all: | $(LIBMLX42)					#build mlx42 once (and first)
all: libft objs $(NAME)				#build other targets every time needed

libft:
	$(MAKE) -C lib/libft -f .unit.mk

objs:								#build objs in parallel
	$(MAKE) -f .unit.mk -j$(nproc) $(OBJS)

clean:
	#clean libft
	$(MAKE) -C lib/libft -f .unit.mk clean
	#clean minirt
	$(info $(RED)Deleting objects$(NOC))
	rm -rf $(BUILD)

fclean: clean
	#full clean libft
	$(MAKE) -C lib/libft -f .unit.mk fclean
	#clean libmlx42
	rm -rf lib/mlx42/build
	#full clean minirt
	$(info $(RED)Deleting binary$(NOC))
	rm -rf $(NAME)

re: fclean all

#******************************************************************************#
#*** BUILD RULES **************************************************************#

$(LIBMLX42):
	cmake lib/mlx42 -B lib/mlx42/build						\
		&& cmake --build lib/mlx42/build -j$(nproc) -- -s

$(NAME): $(MAINOBJ) $(OBJS) $(LIBFT) $(LIBMLX42)
	$(info $(BLUE)Linking C executable $@$(NOC))
	$(CC) $(CFLAGS) $(MAINOBJ) $(OBJS) $(LDFLAGS) -o $@
	$(info $(GREEN)All done$(NOC))

$(DIRS):
	mkdir -p $@

$(OBJS): $(BUILD)/%.o: $(SRC)/%.c | $$(@D)
	$(progress-log)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(MAIN): $(TESTS) | $$(@D)
	$(info $(PURPLE)Building $@ $(NOC))
	./tests/gt-gen $(TESTS) > $@

$(MAINOBJ): $(MAIN) | $$(@D)
	$(info $(PURPLE)Building $@ $(NOC))
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%% COLORS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

NOC			:=	$(shell echo "\033[0m")
RED			:=	$(shell echo "\e[1m\e[38;5;196m")
BLUE		:=	$(shell echo "\e[1m\e[38;5;33m")
GREEN		:=	$(shell echo "\e[1m\e[38;5;76m")
PURPLE		:=	$(shell echo "\033[1;35m")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%% PROGRESS LOG UTILS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

objs: export N		:=	0
objs: export NTOTAL	?=	\
	$(shell make NTOTAL=1 -f .unit.mk -n $(OBJS) | grep clang | wc -l)

define progress-log =
	$(info [$(words $(N))/$(NTOTAL)] $(PURPLE)Building $@ $(NOC))
	$(eval N += 1)
endef
