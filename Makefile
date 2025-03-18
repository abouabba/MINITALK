NAME_S = server

NAME_C = client

NAME_BONUS_S = server_bonus

NAME_BONUS_C = client_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_S = mandatory/server.c mandatory/utils.c

SRC_C = mandatory/client.c mandatory/utils.c

SRC_BONUS_S = bonus/server_bonus.c bonus/utils_bonus.c

SRC_BONUS_C = bonus/client_bonus.c bonus/utils_bonus.c

all: $(NAME_S) $(NAME_C)

bonus: $(NAME_BONUS_S) $(NAME_BONUS_C)

$(NAME_BONUS_S): $(SRC_BONUS_S)
	$(CC) $(CFLAGS) $(SRC_BONUS_S) -o $(NAME_BONUS_S)

$(NAME_BONUS_C): $(SRC_BONUS_C)
	$(CC) $(CFLAGS) $(SRC_BONUS_C) -o $(NAME_BONUS_C)

$(NAME_S): $(SRC_S)
	$(CC) $(CFLAGS) $(SRC_S) -o $(NAME_S)

$(NAME_C): $(SRC_C)
	$(CC) $(CFLAGS) $(SRC_C) -o $(NAME_C)

clean:
	rm -f $(NAME_S) $(NAME_C) $(NAME_BONUS_S) $(NAME_BONUS_C)

fclean: clean

re: fclean all
