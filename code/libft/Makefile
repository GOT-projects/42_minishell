# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 22:49:51 by jmilhas           #+#    #+#              #
#    Updated: 2022/02/04 01:16:56 by aartiges         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

#Setting Color
CCEND 		=   	\033[0m
CCYAN 		=   	\033[34m
CGREEN		=   	\033[33m
CCRED 		=   	\033[31m
CCPURPLE 	=   	\033[35m

NAME 		=	libft.a
EXEC 		= 	libft
CC 		= 	gcc

PATH_CONV	=	./conv/
PATH_ISA	=	./isa/
PATH_MEM	=	./mem/
PATH_STR	=	./str/
PATH_PRINT	=	./print/
PATH_LST	=	./lst/
PATH_OBJ	=	./objs/

CONV 		=     	ft_atoi.c			\
			ft_atoll.c			\
			ft_atoi_base.c			\
			ft_dec_to_bin.c			\
			ft_binary_len.c			\
			ft_itoa.c
OBJS_CONV	=	$(CONV:.c=.o)

ISA		=	ft_isalnum.c	   		\
			ft_isalpha.c	   		\
			ft_isascii.c	   		\
			ft_isa_white_space.c		\
			ft_isdigit.c	   		\
			ft_isprint.c
OBJS_ISA	=	$(ISA:.c=.o)

MEM		=	ft_bzero.c	   		\
			ft_calloc.c      		\
			ft_create_tab_int.c		\
			ft_strdup.c	   		\
			ft_strndup.c	   		\
			ft_strdupcat.c			\
			ft_memalloc.c   		\
			ft_memchr.c	   		\
			ft_memcmp.c	   		\
			ft_memcpy.c	   		\
			ft_memmove.c	  		\
			ft_memset.c	   	        \
			ft_add_mal.c	   	        \
			ft_error_mal.c	   	        \
			ft_track_free_all.c  	        \
			ft_track_free_tab.c 	        \
			ft_freetab.c
OBJS_MEM	=	$(MEM:.c=.o)
	
STR		=	ft_split.c       		\
			ft_strsplit.c       		\
			ft_strchr.c	 		\
			ft_strichr.c	 		\
			ft_strcpy.c	   		\
			ft_strncat.c	   		\
			ft_striteri.c    		\
			ft_strjoin.c			\
			ft_strjoin.c	   		\
			ft_strlcat.c	   		\
			ft_strcat.c	   		\
			ft_strlcpy.c    		\
			ft_strlen.c	   		\
			ft_strmapi.c    		\
			ft_strcmp.c	   		\
			ft_strncmp.c	   		\
			ft_strnstr.c	   		\
			ft_strrchr.c	   		\
			ft_strtrim.c     		\
			ft_substr.c   			\
			ft_tolower.c	   		\
			ft_toupper.c	   		\
			ft_join.c	   		\
      			ft_strcpy.c
OBJS_STR	=	$(STR:.c=.o)

PRINT		=	ft_putchar_fd.c  	        \
			ft_putendl_fd.c  		\
			ft_putnbr_fd.c   		\
			ft_putstr_fd.c
OBJS_PRINT	=	$(PRINT:.c=.o)

LST	=		ft_lstadd_back.c 		\
			ft_lstadd_front.c		\
			ft_lstclear.c    		\
			ft_lstdelone.c   		\
			ft_lstiter.c     		\
			ft_lstlast.c     		\
			ft_lstnew.c			\
			ft_lstsize.c
OBJS_LST	=	$(LST:.c=.o)

#dir .o
CONV_O		=	$(addprefix $(PATH_CONV), $(CONV))
ISA_O		=	$(addprefix $(PATH_ISA), $(ISA))
MEM_O		=	$(addprefix $(PATH_MEM), $(MEM))
STR_O		=	$(addprefix $(PATH_STR), $(STR))
PRINT_O		=	$(addprefix $(PATH_PRINT), $(PRINT))
LST_O		=	$(addprefix $(PATH_LST), $(LST))

#dir obj/.o
OBJ_ISA		=	$(addprefix $(PATH_OBJ), $(OBJS_ISA))
OBJ_MEM		=	$(addprefix $(PATH_OBJ), $(OBJS_MEM))
OBJ_STR		=	$(addprefix $(PATH_OBJ), $(OBJS_STR))
OBJ_PRINT	=	$(addprefix $(PATH_OBJ), $(OBJS_PRINT))
OBJ_LST		=	$(addprefix $(PATH_OBJ), $(OBJS_LST))
OBJ_C		=	$(addprefix $(PATH_OBJ), $(OBJS_CONV))

HEADER 		= 	include/libft.h
FLAGS 		= 	-Wall -Werror -Wextra
MK 		= 	Makefile

$(PATH_OBJ)%.o : $(PATH_CONV)%.c $(HEADER) $(MK)
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@-$(CC) $(FLAGS) -I ./includes -o $@ -c $<
	@printf "\r\t\033[K$(CCYAN)\t$< $(CCPURPLE)--> $(CCYAN)$@ $(CCEND)"
#	@sleep 0.02
$(PATH_OBJ)%.o : $(PATH_ISA)%.c $(HEADER) $(MK)
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@-$(CC) $(FLAGS) -I ./includes -o $@ -c $<
	@printf "\r\t\033[K$(CCYAN)\t$< $(CCPURPLE)--> $(CCYAN)$@ $(CCEND)"
#	@sleep 0.02
$(PATH_OBJ)%.o : $(PATH_MEM)%.c $(HEADER) $(MK)
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@-$(CC) $(FLAGS) -I ./includes -o $@ -c $<
	@printf "\r\t\033[K$(CCYAN)\t$< $(CCPURPLE)--> $(CCYAN)$@ $(CCEND)"
#	@sleep 0.02
$(PATH_OBJ)%.o : $(PATH_STR)%.c $(HEADER) $(MK)
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@-$(CC) $(FLAGS) -I ./includes -o $@ -c $<
	@printf "\r\t\033[K$(CCYAN)\t$< $(CCPURPLE)--> $(CCYAN)$@ $(CCEND)"
#	@sleep 0.02
$(PATH_OBJ)%.o : $(PATH_PRINT)%.c $(HEADER) $(MK)
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@-$(CC) $(FLAGS) -I ./includes -o $@ -c $<
	@printf "\r\t\033[K$(CCYAN)\t$< $(CCPURPLE)--> $(CCYAN)$@ $(CCEND)"
#	@sleep 0.02
$(PATH_OBJ)%.o : $(PATH_LST)%.c $(HEADER) $(MK)
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@-$(CC) $(FLAGS) -I ./includes -o $@ -c $<
	@printf "\r\t\033[K$(CCYAN)\t$< $(CCPURPLE)--> $(CCYAN)$@ $(CCEND)"
#	@sleep 0.02

all: $(NAME)

$(NAME): $(OBJ_C) $(OBJ_ISA) $(OBJ_MEM) $(OBJ_STR) $(OBJ_PRINT) $(OBJ_LST)
	@printf "\r\t\033[K$(CCYAN)[✅]\t$(EXEC) $(CCPURPLE)--> $(CCYAN)Gen Objs$(CCEND)"
	@printf "\n$(CCYAN)[✅]\t$(CCPURPLE)Creation of Objs $(EXEC)...$(CCEND)\n"
	@printf "$(CCYAN)[✅]\t$(CCPURPLE)Creation of $(NAME)...$(CCEND)\n"
	@ar rc $(NAME) $(OBJ_ISA) $(OBJ_MEM) $(OBJ_STR) $(OBJ_PRINT) $(OBJ_LST) $(OBJ_C)


clean:
	@printf "$(CCYAN)[✅]\t$(CCRED)Removal of $(EXEC) Objects...$(CCEND)\n"
	@-/bin/rm -rf $(PATH_OBJ)

fclean: clean
	@printf "$(CCYAN)[✅]\t$(CCRED)Removal of $(NAME)...$(CCEND)\n"
	@-/bin/rm -f $(NAME)

re: fclean all 

norm:
	@norminette || true
