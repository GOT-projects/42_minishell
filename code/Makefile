# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 19:20:00 by aartiges          #+#    #+#              #
#    Updated: 2022/03/08 00:19:03 by aartiges &       ###   ########lyon.fr    #
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

# Headers

DIR_HDS				=	includes

RELATIVE_HDS		=	mini_shell.h	\
						struct.h		\
						define_common.h	\
						includes.h

RELATIVE_HDS_BONUS	=	mini_shell.h	\
						struct_bonus.h	\
						define_common.h	\
						includes.h

# Code

DIR_GLOBAL					=	.
SRC_GLOBAL					=	main.c

DIR_DEBUG					=	debug
SRC_DEBUG					=	tree.c						\
								tree_utils.c
SRC_DEBUG_BONUS				=	tree_bonus.c				\
								tree_utils.c


DIR_BUILTIN					=	srcs/builtin
SRC_BUILTIN					=	env.c						\
								export.c					\
								unset.c						\
								exit.c						\
								echo.c						\
								pwd.c						\
								cd.c						\
								cd_utils.c

DIR_SIGNAL					=	srcs/signal
SRC_SIGNAL					=	interactve_mode.c			\
								exec_mode.c


DIR_EXEC					=	srcs/exec
SRC_EXEC					=	exec_cmd.c 					\
								exec_prg.c 					\
								exec_prg_error.c 			\
								exec.c						\
								exec_pipe.c 				\
								exec_redirection.c 			\
								exec_redir_utils.c			\
								exec_pipe_utils.c				
SRC_EXEC_BONUS				=	exec_cmd.c 					\
								exec_prg.c 					\
								exec_prg_error.c 			\
								exec_bonus.c				\
								exec_pipe.c 				\
								exec_redirection.c 			\
								exec_redir_utils.c			\
								exec_pipe_utils.c 			\
								exec_bool_bonus.c 			\
								exec_sub_shell_bonus.c


DIR_PARSING_SYNTAX			=	srcs/parsing/syntax
SRC_PARSING_SYNTAX			=	check_syntax.c
SRC_PARSING_SYNTAX_BONUS	=	check_syntax_bonus.c 		\
								check_syntax_utils_bonus.c

DIR_PARSING_PROMPT			=	srcs/parsing/prompt
SRC_PARSING_PROMPT			=	get_forgot.c 				\
								check_syntax.c				\
								prompt.c					\
								get_heredoc.c
SRC_PARSING_PROMPT_BONUS	=	get_forgot.c 				\
								check_syntax_bonus.c		\
								prompt.c					\
								check_syntax_utils_bonus.c	\
								get_heredoc.c


DIR_PARSING_TRANSFORM		=	srcs/parsing/transform
SRC_PARSING_TRANSFORM		=	split_str.c					\
								split_str_utils.c			\
								ft_replace_var_env.c		\
								ft_replace_var_tool.c		\
								ft_replace_var_tool1.c		\
								ft_check_var_is_empty.c		\
								ft_quote_tool.c				\
								ft_quote.c
SRC_PARSING_TRANSFORM_BONUS	=	split_str_bonus.c			\
								split_str_utils_bonus.c		\
								ft_replace_var_env.c		\
								ft_replace_var_tool.c		\
								ft_replace_var_tool1.c		\
								ft_quote_tool.c				\
								ft_quote.c					\
								wildcard_bonus.c			\
								wildcard_checker.c			\
								wildcard_tools_bonus.c		\
								ft_check_var_is_empty.c		\
								wildcard_tools1_bonus.c		\
								wildcard_tools2_bonus.c


DIR_PARSING_TREE			=	srcs/parsing/tree
SRC_PARSING_TREE			=	cmd.c						\
								construct_childs.c			\
								lst_childs.c 				\
								pipe.c						\
								redirection.c
SRC_PARSING_TREE_BONUS		=	cmd.c						\
								construct_childs_bonus.c	\
								sub_shell_bonus.c			\
								bool_bonus.c				\
								lst_childs.c 				\
								pipe.c						\
								redirection.c

DIR_PARSING					=	srcs/parsing
SRC_PARSING					=	parse.c						\
								utils.c
SRC_PARSING_BONUS			=	parse_bonus.c				\
								utils_bonus.c				\
								utils_2_bonus.c

DIR_ENV						=	srcs/env
SRC_ENV						=	lst_env.c					\
								env_utils.c					\
								ft_get_env.c				\
								get_path.c

MK							=	Makefile

################################################################################
##                       Compilation Environnement                            ##
################################################################################

NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -O3 -g3
# -fsanitize=address

# Includes lib readline

UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		INC_LIB = -L/usr/local/lib
		INC_INC = -I/usr/local/include
	endif
	ifeq ($(UNAME_S),Darwin)
		INC_LIB = -L ~/.brew/opt/readline/lib
		INC_INC = -I ~/.brew/opt/readline/include
	endif

LIBS	=	$(INC_LIB) $(INC_INC) -lreadline

# libft

DIR_LIBFT			= 	libft
LIBFT_NAME			=	$(DIR_LIBFT)/libft.a

# Sources

DIRS_SRC			=	$(DIR_GLOBAL)				\
						$(DIR_BUILTIN)				\
						$(DIR_DEBUG)				\
						$(DIR_ENV)					\
						$(DIR_EXEC)					\
						$(DIR_SIGNAL)				\
						$(DIR_PARSING_SYNTAX)		\
						$(DIR_PARSING_TRANSFORM)	\
						$(DIR_PARSING_PROMPT)		\
						$(DIR_PARSING_TREE) 		\
						$(DIR_PARSING)

DIR_OBJ				=	obj

SRCS		=	$(addprefix $(DIR_GLOBAL)/, $(SRC_GLOBAL))							\
				$(addprefix $(DIR_DEBUG)/, $(SRC_DEBUG))							\
				$(addprefix $(DIR_BUILTIN)/, $(SRC_BUILTIN))						\
				$(addprefix $(DIR_ENV)/, $(SRC_ENV))								\
				$(addprefix $(DIR_EXEC)/, $(SRC_EXEC))								\
				$(addprefix $(DIR_SIGNAL)/, $(SRC_SIGNAL))							\
				$(addprefix $(DIR_PARSING)/, $(SRC_PARSING))						\
				$(addprefix $(DIR_PARSING_TRANSFORM)/, $(SRC_PARSING_TRANSFORM))	\
				$(addprefix $(DIR_PARSING_PROMPT)/, $(SRC_PARSING_PROMPT))			\
				$(addprefix $(DIR_PARSING_TREE)/, $(SRC_PARSING_TREE))				\
				$(addprefix $(DIR_PARSING_SYNTAX)/, $(SRC_PARSING_SYNTAX))

SRCS_BONUS	=	$(addprefix $(DIR_GLOBAL)/, $(SRC_GLOBAL))								\
				$(addprefix $(DIR_BUILTIN)/, $(SRC_BUILTIN))							\
				$(addprefix $(DIR_SIGNAL)/, $(SRC_SIGNAL))								\
				$(addprefix $(DIR_ENV)/, $(SRC_ENV))									\
				$(addprefix $(DIR_DEBUG)/, $(SRC_DEBUG_BONUS))							\
				$(addprefix $(DIR_EXEC)/, $(SRC_EXEC_BONUS))							\
				$(addprefix $(DIR_PARSING)/, $(SRC_PARSING_BONUS))						\
				$(addprefix $(DIR_PARSING_TRANSFORM)/, $(SRC_PARSING_TRANSFORM_BONUS))	\
				$(addprefix $(DIR_PARSING_PROMPT)/, $(SRC_PARSING_PROMPT_BONUS))		\
				$(addprefix $(DIR_PARSING_TREE)/, $(SRC_PARSING_TREE_BONUS))			\
				$(addprefix $(DIR_PARSING_SYNTAX)/, $(SRC_PARSING_SYNTAX_BONUS))


ifeq ($(MAKECMDGOALS), bonus)
CFLAGS		+= -DBONUS=1
HDS			=	$(addprefix $(DIR_HDS)/, $(RELATIVE_HDS_BONUS))
OBJS		=	$(addprefix $(DIR_OBJ)/, $(SRCS_BONUS:.c=.o))
else
HDS			=	$(addprefix $(DIR_HDS)/, $(RELATIVE_HDS))
OBJS		=	$(addprefix $(DIR_OBJ)/, $(SRCS:.c=.o))
endif

DEPENDS		=	$(HDS) $(MK) $(LIBFT_NAME)

################################################################################
##                                 Règles                                     ##
################################################################################

all	:	$(NAME)
bonus	:	$(NAME)

define src2obj
$(DIR_OBJ)/$(1)/%.o:	$(1)/%.c $(2)
	@mkdir -p $(DIR_OBJ)/$(1)
	@printf "\r\033[K\tCompilation of $(COLOR_PURPLE)$$< ==> $$@\$(COLOR_NORM)"
	@$(CC) $(CFLAGS) -c -o $$@ $$< $(INC_INC)
endef

$(foreach dir,$(DIRS_SRC),$(eval $(call src2obj,$(dir), $(DEPENDS))))

$(LIBFT_NAME):
	@make -C $(DIR_LIBFT)

$(NAME)	: $(DEPENDS) $(OBJS)
	@printf "\n\tCompilation of $(COLOR_PURPLE)$(NAME)\$(COLOR_NORM)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_NAME) $(LIBS)

l_clean:
	@printf "\tDelete $(COLOR_RED)$(DIR_OBJ)/$(COLOR_NORM) of $(NAME)\n"
	@rm -rf $(DIR_OBJ)

clean:	l_clean
	@make -C $(DIR_LIBFT) clean

fclean:	l_clean
	@make -C $(DIR_LIBFT) fclean
	@printf "\tDelete $(COLOR_RED)$(NAME)$(COLOR_NORM)\n"
	@rm -rf $(NAME)

xclean:
	@rm -rf $(NAME)

re:	fclean all

norm:
	@make -C $(DIR_LIBFT) norm || true
	@norminette	$(HDS) $(SRCS) $(SRCS_BONUS) || true

.PHONY: all clean fclean re bonus xclean norm 
