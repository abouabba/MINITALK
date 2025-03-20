# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 09:41:55 by abouabba          #+#    #+#              #
#    Updated: 2025/03/20 18:10:11 by abouabba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME_C = client
NAME_S = server
NAME_C_BONUS = client_bonus
NAME_S_BONUS = server_bonus
HEADER_FILE = minitalk.h

HELP_FILE = utile.c
SRC_C = client.c
SRC_S = server.c

SRC_C_BONUS = client_bonus.c
SRC_S_BONUS = server_bonus.c

OBJ_C = $(SRC_C:.c=.o)
OBJ_S = $(SRC_S:.c=.o)
OBJ_HELP = $(HELP_FILE:.c=.o)

OBJ_C_BONUS = $(SRC_C_BONUS:.c=.o)
OBJ_S_BONUS = $(SRC_S_BONUS:.c=.o)

all: client server

client: $(OBJ_C) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_C) $(OBJ_HELP) -o $(NAME_C)

server: $(OBJ_S) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_S) $(OBJ_HELP) -o $(NAME_S)

client_bonus: $(OBJ_C_BONUS) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_C_BONUS) $(OBJ_HELP) -o $(NAME_C_BONUS)

server_bonus: $(OBJ_S_BONUS) $(OBJ_HELP)
	$(CC) $(CFLAGS) $(OBJ_S_BONUS) $(OBJ_HELP) -o $(NAME_S_BONUS)

bonus: client_bonus server_bonus

%.o: %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_C) $(OBJ_S) $(OBJ_C_BONUS) $(OBJ_S_BONUS) $(OBJ_HELP)

fclean: clean
	rm -f $(NAME_C) $(NAME_S) $(NAME_C_BONUS) $(NAME_S_BONUS)

re: fclean all
