# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktlili <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 23:32:37 by ktlili            #+#    #+#              #
#    Updated: 2018/10/06 19:30:38 by ktlili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select 

SRC_PATH = ./

SRC_NAME = main.c set_cursor.c signal_handling.c parser.c render_display.c map_key.c termcap_switch.c 

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB = ./lib/libft.a

FLAGS = -ggdb 

LFLAGS = -l ncurses

GC = clang

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all:	$(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./lib/
	$(GC) $(OBJ) $(LIB) $(LFLAGS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	$(GC) -I. $(FLAGS) -o $@ -c $<

clean:
	$(MAKE) -C ./lib/ clean
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) -C ./lib/ fclean
	/bin/rm -f $(NAME)

re: fclean all
