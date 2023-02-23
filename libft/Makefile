# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2023/02/23 13:10:49 by aderouba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS		:=	--no-print-directory
.DEFAULT_GOAL	:=	all
.DELETE_ON_ERROR:
.SECONDEXPANSION:
SHELL			:= bash
.SHELLFLAGS		:= -c
#=================================COMPILATION==================================#
CC		:=	clang
CFLAGS	:=	-MP -MMD -Wall -Wextra -Werror -I .

#==================================EXECUTABLE==================================#
NAME	:=	libft.a
BUILD	:=	.build

#=================================SOURCE FILES=================================#
SRCS	:=	ft_atof.c \
			ft_atoi_base.c \
			ft_atoi.c \
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

#====================================OBJECTS===================================#
OBJS	:=	${SRCS:%.c=$(BUILD)/%.o}
DEPS	:=	$(SRCS:%.c=$(BUILD)/%.d)
DIRS	:=	$(BUILD)

#====================================COLORS====================================#
NOC			:=	\033[0m
RED			:=	\e[1m\e[38;5;196m
GREEN		:=	\e[1m\e[38;5;76m
BLUE		:=	\e[1m\e[38;5;33m
PURPLE		:=	\033[1;35m

#================================PROGRESS BAR UTILS============================#
NB_COMPIL2			:=	0
TOTAL_COMPIL2		:=	$(words $(OBJS))

#=====================================RULES====================================#
$(DIRS):
	@mkdir -p $@

$(BUILD)/%.o : %.c | $$(@D)
	$(if $(filter $(NB_COMPIL2),0), @echo -e "$(BLUE)Compiling libft$(NOC)")
	$(eval NB_COMPIL2=$(shell expr $(NB_COMPIL2) + 1))
	@echo -e "[$(NB_COMPIL2)/$(TOTAL_COMPIL2)] $(PURPLE)Compiling $< $(NOC)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	@echo -e "$(BLUE)Creation of library$(NOC)"
	@ar cr $@ $^
	@echo -e "$(GREEN)Finish !$(NOC)"

all : $(NAME)

clean :
	@echo -e "$(RED)Deleting libft objects$(NOC)"
	@rm -rf $(BUILD)

fclean : clean
	@echo -e "$(RED)Deleting libft$(NOC)"
	@rm -f $(NAME)

re :
	@make fclean
	@make $(NAME) RECURSIVE=1

norm:
	@{ ! norminette $(SRC) $(SRC_BONUS) | grep Error; } && echo -e "$(GREEN)All normed !$(NOC)";

.PHONY: all clean fclean re norm

-include $(DEPS)
