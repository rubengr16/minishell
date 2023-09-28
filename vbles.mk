# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    vbles.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 19:42:48 by rgallego          #+#    #+#              #
#    Updated: 2023/09/07 12:52:56 by rgallego         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=		src/

PARSER_DIR	=		parser/

LEXER_DIR	=		lexer/

ENV_DIR		=		enviroment/

BUILTINS_DIR	=	builtins/

EXEC_DIR	=		executor/

UTILS_DIR	=		utils/

SIGNALS_DIR	=		signals/

INC_DIR		=		inc/

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
					real_token.c \
					lexer.c \
					)

EXECUTOR		=	$(addprefix $(EXEC_DIR), \
					execute.c \
					verify_command.c \
					utils.c \
					redirect.c \
					redirect_utils.c \
					)

ENVIROMENT	=		$(addprefix $(ENV_DIR), \
					enviroment.c \
					get_env.c \
					)

BUILTINS	=	$(addprefix $(BUILTINS_DIR), \
					ft_cd.c \
					ft_echo.c \
					ft_env.c \
					ft_export.c \
					ft_unset.c \
					ft_pwd.c \
					ft_exit.c \
					)

UTILS		=		$(addprefix $(UTILS_DIR), \
					utils.c \
					)

SIGNALS		=		$(addprefix $(SIGNALS_DIR), \
					signals.c \
					)

SRCS		= 		$(addprefix $(SRC_DIR), \
					$(MINISHELL) \
					$(PARSER) \
					$(LEXER) \
					$(ENVIROMENT) \
					$(BUILTINS) \
					$(EXECUTOR) \
					$(UTILS) \
					$(SIGNALS) \
					)

OBJS	=			$(SRCS:.c=.o)

DPNDS	=			$(SRCS:.c=.d)

CC		=			gcc

RM		=			-rm -f

CFLAGS	=			-Wall -Werror -Wextra -MD

RDLINE_INC	=		-I ~/.brew/opt/readline/include

RDLINE_LIB	=		-L ~/.brew/opt/readline/lib

LDFLAGS	=			$(LIBFTNAME)

NAME	=			minishell

INC_ALL	=			\
					$(INC_DIR) \
					$(LIBFT)$(INC_DIR)

LIB_ALL = 			\
					readline

LIBFT	=			libft/

LIBFTNAME	=		$(LIBFT)libft.a
