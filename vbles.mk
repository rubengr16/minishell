# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    vbles.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 19:42:48 by rgallego          #+#    #+#              #
#    Updated: 2023/06/23 01:01:32 by rgallego         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR	=			src/

PARSER_DIR		=	parser/

INC_DIR	=			inc/

MINISHELL	=		main.c

PARSER		=		$(addprefix $(PARSER_DIR), \
					token_lst.c \
					tokenize.c \
					expand.c \
					)

SRCS	= 			$(addprefix $(SRC_DIR), \
					$(MINISHELL) \
					$(PARSER) \
					)

OBJS	=			$(SRCS:.c=.o)

DPNDS	=			$(SRCS:.c=.d)

CC		=			gcc

RM		=			-rm -f

CFLAGS	=			-Wall -Werror -Wextra -MD -fsanitize=address -g3

LDFLAGS	=			$(LIBFTNAME)

NAME	=			minishell

INC_ALL	=			\
					$(INC_DIR) \
					$(LIBFT)$(INC_DIR)

LIB_ALL = 			\
					readline

LIBFT	=			libft/

LIBFTNAME	=		$(LIBFT)libft.a
