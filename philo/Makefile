SRC = libc.c philo.c philo_utils.c philo_time.c philo_routine.c mutex_init.c \
	 	initialize.c philo_state.c error.c
NAME = philo
CC = cc
OBJS = $(addprefix obj/, $(SRC:.c=.o))
INC = philo.h
OS = ${shell uname -s}

ifeq (${OS}, Linux)
	FLAGS = -Wall -Wextra -Werror -pthread
else
	FLAGS = -Wall -Wextra -Werror
endif

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
