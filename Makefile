NAME = minishell
CC = cc
RM = rm -f
#FLAGS = -Wall -Werror -Wextra
FLAGS = -Wall -Wextra -lreadline

SRCS = 	minishell.c \
		src/builtin/ft_echo.c \
		src/builtin/ft_pwd.c \
		src/builtin/ft_cd.c \
		src/builtin/ft_export.c \
		src/builtin/ft_unset.c \
		src/builtin/ft_env.c \
		src/builtin/ft_exit.c \
		src/env/env.c \
		src/env/env_var_handle.c \
		src/env/env_var_handle_utils.c 

OBJS = ${SRCS:.c=.o}
LFLAGS  = -Llibft -lft
LIBFT = libft

all:${OBJS}
	make -C ${LIBFT}
	${CC} ${FLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

.c.o:
	${CC} $(FLAGS) -c $< -o $@

${NAME}: all
clean:
	${RM} ${OBJS}
	make clean -C ${LIBFT}

fclean: 
	make fclean -C ${LIBFT}
	${RM} ${OBJS}
	rm ${NAME}

re: clean all

.PHONY: all clean fclean re
