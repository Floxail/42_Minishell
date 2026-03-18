NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror

SRCS =	minishell.c \
		src/parsing/ft_lexer.c \
		src/parsing/ft_lexer_word.c \
		src/parsing/ft_lexer_op.c \
		src/parsing/ft_token_utils.c \
		src/parsing/ft_expander.c \
		src/parsing/ft_expand_utils.c \
		src/parsing/ft_parser.c \
		src/parsing/ft_parser_syntax.c \
		src/parsing/ft_cmd_utils.c \
		src/parsing/ft_redir_utils.c \
		src/utils/ft_free_cmds.c \
		src/utils/ft_errmsg.c \
		src/executor/ft_executor.c \
		src/executor/ft_exec_child.c \
		src/executor/ft_exec_path.c \
		src/executor/ft_exec_redir.c \
		src/executor/ft_exec_heredoc.c

OBJS = ${SRCS:.c=.o}
LFLAGS = -Llibft -lft -lreadline
LIBFT = libft

all: ${LIBFT} ${NAME}

${LIBFT}:
	make -C ${LIBFT}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

.c.o:
	${CC} ${FLAGS} -c $< -o $@

clean:
	${RM} ${OBJS}
	make clean -C ${LIBFT}

fclean: clean
	make fclean -C ${LIBFT}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re ${LIBFT}
