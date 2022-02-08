# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 19:20:00 by aartiges          #+#    #+#              #
#    Updated: 2022/02/05 00:55:14 by aartiges         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

################################################################################
##                               Présentation                                 ##
################################################################################

COLOR_NORM		=	\033[0m
COLOR_RED		=	\033[31m
COLOR_PURPLE	=	\033[35m

################################################################################
##                               SRCS                                         ##
################################################################################

DIR_HDS			=	includes/

RELATIVE_HDS	=	mini_shell.h	\
					struct.h

SRC_GLOBAL		=	main.c
DIR_GLOBAL			=	.

SRC_BUILTIN		=	env.c		\
					export.c	\
					unset.c		\
					exit.c		\
					echo.c		
#					pwd.c		
#					cd.c		
DIR_BUILTIN		=	srcs/builtin

SRC_ENV			=	get_envp.c		\
					lst_env.c	\
					lst_to_tab.c
DIR_ENV			=	srcs/env

MK				=	Makefile

################################################################################
##                       Compilation Environnement                            ##
################################################################################

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -O3
#-fsanitize=address
LIBS		=	-L/usr/local/lib -I/usr/local/include -lreadline -I$(DIR_HDS)
DIR_LIBFT	= 	libft
LIBFT_NAME	=	$(DIR_LIBFT)/libft.a

SRCS		=	$(addprefix $(DIR_GLOBAL)/, $(SRC_GLOBAL))	\
				$(addprefix $(DIR_BUILTIN)/, $(SRC_BUILTIN))	\
				$(addprefix $(DIR_ENV)/, $(SRC_ENV))
DIRS_SRC	=	$(DIR_GLOBAL) $(DIR_BUILTIN) $(DIR_ENV)
DIR_OBJ		=	obj
OBJS		=	$(addprefix $(DIR_OBJ)/, $(SRCS:.c=.o))
HDS			=	$(addprefix $(DIR_HDS)/, $(RELATIVE_HDS))

DEPENDS		=	$(HDS) $(MK) $(LIBFT_NAME)

################################################################################
##                                 Règles                                     ##
################################################################################

all	:	$(NAME)

define src2obj
$(DIR_OBJ)/$(1)/%.o:	$(1)/%.c $(2)
	@mkdir -p $(DIR_OBJ)/$(1)
	@printf "\r\033[K\tCompilation of $(COLOR_PURPLE)$$< ==> $$@\$(COLOR_NORM)"
	@$(CC) $(CFLAGS) -c -o $$@ $$<
endef

$(foreach dir,$(DIRS_SRC),$(eval $(call src2obj,$(dir), $(DEPENDS))))

$(NAME)	:	$(DEPENDS) $(OBJS)
	@printf "\n\tCompilation of $(COLOR_PURPLE)$(NAME)\$(COLOR_NORM)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_NAME) $(LIBS)

$(LIBFT_NAME)	:
	@make -C $(DIR_LIBFT)

l_clean:
	@printf "\tDelete $(COLOR_RED)$(DIR_OBJ)/$(COLOR_NORM) of $(NAME)\n"
	@rm -rf $(DIR_OBJ)

clean:	l_clean
	@make -C $(DIR_LIBFT) clean

fclean:	l_clean
	@make -C $(DIR_LIBFT) fclean
	@printf "\tDelete $(COLOR_RED)$(NAME)$(COLOR_NORM)\n"
	@rm -rf $(NAME)

re:	fclean all

norm:
	@make -C $(DIR_LIBFT) norm || true
	@norminette	$(HDS)	$(SRCS) || true
