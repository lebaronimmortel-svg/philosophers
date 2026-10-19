NAME = philo

SRC = srcs/main.c \
	  srcs/philo_action.c \
	  srcs/utils.c \
	  srcs/routine.c \
	  srcs/monitor.c \
	  srcs/init.c

OBJ = $(SRC:.c=.o) 
HEADERS = header.h
CC = cc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
