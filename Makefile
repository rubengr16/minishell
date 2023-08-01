# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 18:55:39 by rgallego          #+#    #+#              #
#    Updated: 2023/08/01 18:28:39 by socana-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include vbles.mk

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(addprefix -I, $(INC_ALL)) -c $< -o $@

$(LIBFTNAME):
	$(MAKE) -C $(LIBFT)

$(GNLNAME):
	$(MAKE) -C $(GNL)

$(NAME): $(OBJS) $(LDFLAGS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFTNAME) $(GNLNAME) $(addprefix -l, $(LIB_ALL)) -o $@

clean:
	$(RM) $(OBJS) $(DPNDS)
	$(MAKE) -C $(LIBFT) fclean
	$(MAKE) -C $(GNL) fclean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
