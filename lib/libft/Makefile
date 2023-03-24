# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2023/03/24 17:16:17 by tdubois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS		:=	--no-print-directory

.DELETE_ON_ERROR:
.SECONDEXPANSION:

#==============================================================================#
#=== GOALS ====================================================================#

NAME	:=	libft.a

#==============================================================================#
#=== DIRECTORIES ==============================================================#

BUILD	:=	.build

#==============================================================================#
#=== COMPILATION ==============================================================#

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror
CPPFLAGS	:=	-MP -MMD -I .

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

#==============================================================================#
#=== COLORS ===================================================================#

NOC			:=	\033[0m
RED			:=	\e[1m\e[38;5;196m
GREEN		:=	\e[1m\e[38;5;76m
BLUE		:=	\e[1m\e[38;5;33m
PURPLE		:=	\033[1;35m

#==============================================================================#
#=== PROGRESS BAR UTILS =======================================================#

NB_COMPIL2			:=	0
TOTAL_COMPIL2		:=	$(words $(OBJS))

#******************************************************************************#
#*** PHONY RULES **************************************************************#

.PHONY: all clean fclean re

all: $(NAME)
	@:

clean:
	@rm -rf $(BUILD)

fclean: clean
	@rm -f $(NAME)

re: RECURSIVE=1
re: fclean all

#******************************************************************************#
#*** BUILD RULES **************************************************************#

$(NAME): $(OBJS)
	@echo "$(BLUE)Creation of library$(NOC)"
	@ar rcs $@ $^
	@echo "$(GREEN)Finish !$(NOC)"

$(DIRS):
	@mkdir -p $@

$(OBJS): $(BUILD)/%.o : %.c | $$(@D)
	$(if $(filter $(NB_COMPIL2),0), @echo -e "$(BLUE)Compiling libft$(NOC)")
	$(eval NB_COMPIL2=$(shell expr $(NB_COMPIL2) + 1))
	@echo "[$(NB_COMPIL2)/$(TOTAL_COMPIL2)] $(PURPLE)Compiling $< $(NOC)"
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)
