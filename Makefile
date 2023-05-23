# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2023/05/19 17:38:29 by aderouba         ###   ########.fr        #
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

NAME		:=	minirt

LIBMLX42	:=	lib/mlx42/build/libmlx42.a
LIBFT		:=	lib/libft/libft.a

#==============================================================================#
#=== DIRECTORIES ==============================================================#

SRC			:=	srcs
BUILD		:=	.build

INCLUDES	:=	-Iincludes -Ilib/libft -I/usr/include -Ilib/mlx42/include

#==============================================================================#
#=== COMPILATION ==============================================================#

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -Wno-unused-function -Ofast -std=c99 #TODO
CPPFLAGS	:=	-MP -MMD $(INCLUDES)
LDFLAGS		:=	-Llib/libft -lft			\
				-Llib/mlx42/build -lmlx42	\
				-ldl -lglfw -pthread -lm	\

ifdef DEBUG
CFLAGS		+=	-ggdb3
endif

#==============================================================================#
#=== SOURCES ==================================================================#

#TODO
SRCS	:=	$(shell fd -g '*.c' -E '*.test.c' $(SRC))

# SRCS	:=	srcs/image/ppr.c					\
# 			srcs/image/draw.c					\
# 			srcs/image/ray_tab.c				\
# 			srcs/image/mapping.c				\
# 			srcs/image/color_tab.c				\
# 			srcs/image/antialiasing.c			\
# 			srcs/image/transparency.c			\
# 			srcs/image/merge_pixels.c			\
# 			srcs/image/compute_light.c			\
# 			srcs/image/compute_pixel.c			\
# 			srcs/image/intersections.c			\
# 			srcs/image/calculate_image.c		\
# 			srcs/image/plane_transparency.c		\
# 			srcs/image/sphere_transparency.c	\
# 			srcs/image/incremente_intensity.c	\
# 			srcs/image/cylinder_transparency.c	\
# 			srcs/image/add_diffuse_intensity.c	\
# 			srcs/image/add_specular_intensity.c	\
# 			\
# 			srcs/menu/menu.c							\
# 			srcs/menu/cursor.c							\
# 			srcs/menu/buttons.c							\
# 			srcs/menu/init_menu.c						\
# 			srcs/menu/my_put_string.c					\
# 			srcs/menu/display/display_dir.c				\
# 			srcs/menu/display/display_pos.c				\
# 			srcs/menu/display/display_float.c			\
# 			srcs/menu/display/display_color.c			\
# 			srcs/menu/display/display_light.c			\
# 			srcs/menu/display/display_plane.c			\
# 			srcs/menu/display/display_camera.c			\
# 			srcs/menu/display/display_sphere.c			\
# 			srcs/menu/display/display_cylinder.c		\
# 			srcs/menu/display/display_float_range.c		\
# 			srcs/menu/display/display_ambiant_light.c	\
# 			\
# 			srcs/maths/is_xyz_in_range.c		\
# 			srcs/maths/compute_screen_basis.c	\
# 			\
# 			srcs/objects/camera.c						\
# 			srcs/objects/create_cone.c					\
# 			srcs/objects/create_plane.c					\
# 			srcs/objects/create_sphere.c				\
# 			srcs/objects/intersect_cone.c				\
# 			srcs/objects/space_rotation.c				\
# 			srcs/objects/camera_rotation.c				\
# 			srcs/objects/create_cylinder.c				\
# 			srcs/objects/intersect_plane.c				\
# 			srcs/objects/intersect_sphere.c				\
# 			srcs/objects/camera_translation.c			\
# 			srcs/objects/intersect_cylinder.c			\
# 			srcs/objects/intersect_second_cylinder.c	\
# 			\
# 			srcs/parsing/parse_vec.c		\
# 			srcs/parsing/parse_file.c		\
# 			srcs/parsing/parse_cone.c		\
# 			srcs/parsing/parse_color.c		\
# 			srcs/parsing/parse_float.c		\
# 			srcs/parsing/parse_plane.c		\
# 			srcs/parsing/parse_sphere.c		\
# 			srcs/parsing/parse_camera.c		\
# 			srcs/parsing/parse_lights.c		\
# 			srcs/parsing/parse_cylinder.c	\
# 			srcs/parsing/parse_direction.c	\
# 			\
# 			srcs/utils/rtlst.c						\
# 			srcs/utils/imglst.c						\
# 			srcs/utils/print.c						\
# 			srcs/utils/number.c						\
# 			srcs/utils/string.c						\
# 			srcs/utils/math_utils.c					\
# 			srcs/utils/intersect_ret.c				\
# 			srcs/utils/vec3/vec_creation.c			\
# 			srcs/utils/vec3/vec_operator.c			\
# 			srcs/utils/vec3/vec_get_normals.c		\
# 			srcs/utils/vec3/vec_vec_operator.c		\
# 			srcs/utils/vec3/vec_number_operator.c	\
# 			\
# 			srcs/main.c

#==============================================================================#
#=== BUILD FILES ==============================================================#

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

libft:								#libft may be updated during development,
	$(MAKE) -C lib/libft			#hence it's made a phony target

objs:								#build objs in parallel
	$(MAKE) -j$(nproc) $(OBJS)

clean:
	#clean libft
	$(MAKE) -C lib/libft clean
	#clean minirt
	$(info $(RED)Deleting objects$(NOC))
	rm -rf $(BUILD)

fclean: clean
	#full clean libft
	$(MAKE) -C lib/libft fclean
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

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX42)
	$(info $(BLUE)Linking C executable $@$(NOC))
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	$(info $(GREEN)All done$(NOC))

$(DIRS):
	mkdir -p $@

$(OBJS): $(BUILD)/%.o: $(SRC)/%.c | $$(@D)
	$(progress-log)
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
objs: export NTOTAL	?=	$(shell make NTOTAL=1 -n $(OBJS) | grep clang | wc -l)

define progress-log =
	$(info [$(words $(N))/$(NTOTAL)] $(PURPLE)Building $< $(NOC))
	$(eval N += 1)
endef
