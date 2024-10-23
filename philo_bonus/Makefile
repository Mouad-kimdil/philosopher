SRC = philo_bonus.c philo_init_bonus.c philo_utils_bonus.c libc_bonus.c \
		philo_time_bonus.c philo_state_bonus.c
CC = cc
NAME = philo_bonus
FLAGS = -Wall -Wextra -Werror
OBJS = $(addprefix obj/, $(SRC:.c=.o))
INC = philo_bonus.h

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
