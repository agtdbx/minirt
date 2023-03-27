# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2023/03/27 14:19:09 by tdubois          ###   ########.fr        #
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

NAME		:=	libft.a

#==============================================================================#
#=== DIRECTORIES ==============================================================#

BUILD		:=	.build

#==============================================================================#
#=== COMPILATION ==============================================================#

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -O3
CPPFLAGS	:=	-MP -MMD -I .

ifdef DEBUG
CFLAGS		+=	-ggdb3
endif

#==============================================================================#
#=== SOURCES ==================================================================#

SRCS	:=	ft_atof.c \
			ft_atoi_base.c \
			ft_atoi.c \
			ft_atol.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_ftoa.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprime.c \
			ft_isprint.c \
			ft_itoa_base.c \
			ft_itoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstr.c \
			ft_lstsize.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_pow.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_base_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_putunbr_base_fd.c \
			ft_putunbr_fd.c \
			ft_split.c \
			ft_sqrt.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strcspn.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin_free_1st_p.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strspn.c \
			ft_strstr.c \
			ft_strendswith.c\
			ft_strsuperjoin_free_1st_p.c \
			ft_strsuperjoin.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_supersplit.c \
			ft_tolower.c \
			ft_toupper.c \
			gnl.c \
			printf_fd.c \
			printf.c

#==============================================================================#
#=== BUILD FILES ==============================================================#

OBJS		:=	$(SRCS:%.c=$(BUILD)/%.o)
DEPS		:=	$(SRCS:%.c=$(BUILD)/%.d)
DIRS		:=	$(BUILD)

#******************************************************************************#
#*** PHONY RULES **************************************************************#

.PHONY:	all				\
		objs			\
		clean fclean re

all: objs $(NAME)

objs:								#build objs in parallel
	$(MAKE) -j$(nproc) $(OBJS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

#******************************************************************************#
#*** BUILD RULES **************************************************************#

$(NAME): $(OBJS)
	$(info $(BLUE)Linking C static library $@$(NOC))
	ar rcs $@ $(OBJS)
	$(info $(GREEN)All done$(NOC))

$(DIRS):
	mkdir -p $@

$(OBJS): $(BUILD)/%.o: %.c | $$(@D)
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
