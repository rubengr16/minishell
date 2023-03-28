# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 19:07:41 by rgallego          #+#    #+#              #
#    Updated: 2022/09/21 17:12:04 by rgallego         ###   ########.fr        #
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
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJS) $(DPNDS)
	$(MAKE) -C $(LIBFT) fclean
	$(MAKE) -C $(GNL) fclean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
