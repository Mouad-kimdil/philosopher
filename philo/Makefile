SRC = libc.c philo.c philo_utils.c philo_time.c philo_routine.c mutex_init.c \
	 	initialize.c philo_state.c
NAME = philo
CC = clang
FLAGS = -Wall -Wextra -Werror -fsanitize=thread
OBJS = $(addprefix obj/, $(SRC:.c=.o))
INC = philo.h

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

obj/%.o: %.c ${INC}
	@mkdir -p $(dir $@)
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf ${NAME}

re: fclean all
