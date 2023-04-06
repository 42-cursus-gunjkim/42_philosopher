NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = ./obj/

SRCS = parser.c philo_log.c philo.c spaghetti_time.c philo_utils.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)%.o : %.c
	@test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: fclean
	$(CC) $(CFLAGS) -fsanitize=thread -o $(NAME) $(SRCS)

clean:
	rm -rf philosopher.dSYM
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.phony: all clean fclean re