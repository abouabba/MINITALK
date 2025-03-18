NAME_S = server
NAME_C = client
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_S = server.c utils.c
SRC_C = client.c utils.c

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(SRC_S)
	$(CC) $(CFLAGS) $(SRC_S) -o $(NAME_S)

$(NAME_C): $(SRC_C)
	$(CC) $(CFLAGS) $(SRC_C) -o $(NAME_C)

clean:
	rm -f $(NAME_S) $(NAME_C)

fclean: clean

re: fclean all
