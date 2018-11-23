# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktlili <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 23:32:37 by ktlili            #+#    #+#              #
#    Updated: 2018/11/20 15:11:46 by ktlili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select 

SRC_PATH = ./

SRC_NAME = main.c map_key.c new_map_key.c set_cursor.c signal_handling.c parser.c render_display.c termcap_switch.c set_colors.c tools.c

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB = ./lib/libft.a

FLAGS = -ggdb -Wall -Wextra -Werror

LFLAGS =  -ltermcap

GC = clang

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all:	$(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./lib/
	$(GC) $(OBJ) $(LIB) $(LFLAGS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	$(GC)  $(FLAGS) -o $@ -c $<

clean:
	$(MAKE) -C ./lib/ clean
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) -C ./lib/ fclean
	/bin/rm -f $(NAME)

re: fclean all
