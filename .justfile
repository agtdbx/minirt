# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .justfile                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/25 02:38:56 by tdubois           #+#    #+#              #
#    Updated: 2023/03/25 16:57:49 by tdubois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%% CONFIGURATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

[private]
@default:
	just --list --unsorted --list-prefix '‧‧‧‧ '

GREEN	:=	`echo '\e[92m'`
NC		:=	`echo '\e[0m'`

#==============================================================================#
#=== BUILD ====================================================================#

[private]
alias b	:=	build
[private]
alias r	:=	re
[private]
alias c	:=	clean

#build project
@build:
	make

#rebuild project
@re:
	make re

#clean project
@clean:
	make fclean

#==============================================================================#
#=== TESTS ====================================================================#

[private]
alias t	:=	test

#run all tests
@test: lint
	echo "{{GREEN}}TESTS OK!{{NC}}"

SOURCES	:=	```{
	fd -g '*.c' -E '*.test.c' srcs
	fd -g '*.h' -E '*/greatest.h' includes
} | xargs```

#run static analysis (norminette)
@lint:
	norminette {{SOURCES}} | { ! grep Error; }
