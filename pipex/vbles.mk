SRC_DIR	=			src/

INC_DIR	=			inc/

CMDLIST_DIR	=	cmdlist/

CMDLIST	=		$(addprefix $(CMDLIST_DIR), \
					cmdlist_init.c \
					cmdlist_push.c \
					cmdlist_pop.c \
					cmdlist_del.c \
					)

PIPELIST_DIR	=	pipelist/

PIPELIST	=		$(addprefix $(PIPELIST_DIR), \
					pipelist_init.c \
					pipelist_push.c \
					pipelist_pop.c \
					pipelist_del.c \
					)

SRCS	= 			$(addprefix $(SRC_DIR), \
					main.c \
					utils.c \
					pipex.c \
					error_mgment.c \
					$(CMDLIST) \
					$(PIPELIST) \
					)

OBJS	=			$(SRCS:.c=.o)

DPNDS	=			$(SRCS:.c=.d)

CC		=			gcc

RM		=			-rm -f

CFLAGS	=			-Wall -Werror -Wextra -MD

LDFLAGS	=			\
					$(LIBFTNAME) \
					$(GNLNAME)

NAME	=			pipex

INC_ALL	=			\
					$(INC_DIR) \
					$(LIBFT)$(INC_DIR) \
					$(GNL)$(INC_DIR)

LIBFT	=			libft/

LIBFTNAME	=		$(LIBFT)libft.a

GNL		=			get_next_line/

GNLNAME	=			$(GNL)get_next_line.a
