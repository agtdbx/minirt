# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .justfile                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/25 02:38:56 by tdubois           #+#    #+#              #
#    Updated: 2023/03/31 12:31:24 by tdubois          ###   ########.fr        #
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
	make clean all

#clean project
@clean:
	make fclean

#==============================================================================#
#=== TESTS ====================================================================#

[private]
alias t		:=	test

[private]
alias rt	:=	re-test

#run all tests
@test: unit lint
	echo "{{GREEN}}TESTS OK!{{NC}}"

#rebuild unit tests and run all tests
@re-test: re-unit lint
	echo "{{GREEN}}TESTS OK!{{NC}}"

#*** LINT *********************************************************************#

[private]
alias l		:=	lint

SOURCES	:=	```{
	fd -g '*.c' -E '*.test.c' srcs lib/libft
	fd -g '*.h' -E 'greatest.h' includes lib/libft
} | xargs```

#run static analysis (norminette)
@lint:
	norminette {{SOURCES}} | { ! grep Error; }

#*** UNIT *********************************************************************#

[private]
alias u		:=	unit

[private]
alias ru	:=	re-unit

#run unit tests, with ARGS passed to gt-run
@unit *ARGS:
	make -f .unit.mk
	./tests/gt-run {{ARGS}} ./unit

#rebuild, then run unit tests
@re-unit *ARGS:  && (unit ARGS)
	make -f .unit.mk clean
