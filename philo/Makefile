SRC = libc.c philo.c philo_utils.c philo_time.c
NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
OBJS = $(addprefix obj/, $(SRC:.c=.o))
INC = philo.h

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

obj/%.o: %.c ${INC}
	@mkdir -p $(dir $@)
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all
