# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .justfile                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/25 02:38:56 by tdubois           #+#    #+#              #
#    Updated: 2023/04/05 13:33:56 by tdubois          ###   ########.fr        #
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

#build project
@build:
	make DEBUG=1

#rebuild project
@re: && build
	make clean

#clean project
@clean:
	make fclean

#==============================================================================#
#=== TESTS ====================================================================#

#run all tests
@test: unit lint
	echo "{{GREEN}}TESTS OK!{{NC}}"

#rebuild unit tests and run all tests
@re-test: re-unit lint
	echo "{{GREEN}}TESTS OK!{{NC}}"

#*** LINT *********************************************************************#

SOURCES	:=	```{
	fd -g '*.c' -E '*.test.c' srcs lib/libft
	fd -g '*.h' -E 'greatest.h' includes lib/libft
} | xargs```

#run static analysis (norminette)
@lint:
	norminette {{SOURCES}} | { ! grep Error; }

#*** UNIT *********************************************************************#

#run unit tests, with ARGS passed to gt-run
@unit *ARGS:
	make -f .unit.mk
	./tests/gt-run {{ARGS}} ./unit

#rebuild, then run unit tests
@re-unit *ARGS:  && (unit ARGS)
	make -f .unit.mk clean
