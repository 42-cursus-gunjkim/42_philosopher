NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = ./obj/
SRCS = philo.c log.c parser.c spaghetti_time.c spaghetti_util.c
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)%.o: %.c
	@test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $^

lldbtest:
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS)

threadtest:
	$(CC) $(CFLAGS) -fsanitize=thread -o $(NAME) $(SRCS)

tclean: fclean
	rm -rf philo.dSYM

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
