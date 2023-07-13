# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    vbles.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 19:42:48 by rgallego          #+#    #+#              #
#    Updated: 2023/07/08 21:06:38 by rgallego         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR	=			src/

PARSER_DIR		=	parser/

LEXER_DIR		=	lexer/

UTILS_DIR		=	utils/

INC_DIR	=			inc/

MINISHELL	=		main.c

PARSER		=		$(addprefix $(PARSER_DIR), \
					utils.c \
					token_lst.c \
					tokenize.c \
					)

LEXER		=		$(addprefix $(LEXER_DIR), \
					utils.c \
					redir.c \
					cmd.c \
					expand.c \
					lexer.c \
					)

UTILS		=		$(addprefix $(UTILS_DIR), \
					utils.c \
					)

SRCS	= 			$(addprefix $(SRC_DIR), \
					$(MINISHELL) \
					$(PARSER) \
					$(LEXER) \
					$(UTILS) \
					)

OBJS	=			$(SRCS:.c=.o)

DPNDS	=			$(SRCS:.c=.d)

CC		=			gcc

RM		=			-rm -f

CFLAGS	=			-Wall -Werror -Wextra -MD

LDFLAGS	=			$(LIBFTNAME)

NAME	=			minishell

INC_ALL	=			\
					$(INC_DIR) \
					$(LIBFT)$(INC_DIR)

LIB_ALL = 			\
					readline

LIBFT	=			libft/

LIBFTNAME	=		$(LIBFT)libft.a
