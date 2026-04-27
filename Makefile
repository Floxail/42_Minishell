NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
OBJDIR = obj

SRCS =	minishell.c \
		signals.c \
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
		src/executor/ft_exec_heredoc.c \
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

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
LFLAGS = -Llibft -lft -lreadline
LIBFT = libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)
	make clean -C $(LIBFT)

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re $(LIBFT)
