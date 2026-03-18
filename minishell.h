/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:33:05 by floxail           #+#    #+#             */
/*   Updated: 2026/03/18 10:32:06 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"


typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

/*  Token  (sortie du Lexer : valeur RAW avec quotes conservées)  */

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/*  Redirection  */

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/*  Commande (sortie du Parser)  */

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/*  Contexte interne du Lexer  */

typedef struct s_lex_ctx
{
	char	*input;
	int		i;
	int		in_sq;
	int		in_dq;
	t_token	*list;
}	t_lex_ctx;

/*  Contexte interne de l'Expander  */

typedef struct s_exp_ctx
{
	char	*src;
	int		i;
	char	*result;
	int		in_sq;
	int		in_dq;
}	t_exp_ctx;

/* Lexer */

t_token		*ft_lexer(char *input);
int			ft_is_meta(char c);
int			ft_extract_word(t_lex_ctx *ctx);
int			ft_extract_operator(t_lex_ctx *ctx);

/* Token utils */

int			ft_add_token(t_token **list, char *value, t_token_type type);
void		ft_free_tokens(t_token *list);

/* Expander */

void		ft_expander(t_token *tokens, char **env, int code);
char		*ft_expand_value(char *src, char **env, int code);
char		*ft_get_var_name(char *str, int *i);
char		*ft_get_var_val(char *name, char **env, int code);

/*  Parser */

t_cmd		*ft_parser(t_token *tokens);
int			ft_check_syntax(t_token *tok);
int			ft_is_redir(t_token_type type);

/* Cmd utils */

t_cmd		*ft_new_cmd(void);
int			ft_add_arg(t_cmd *cmd, char *val);
int			ft_add_redir(t_cmd *cmd, t_token_type type, char *file);
void		ft_cmd_addback(t_cmd **list, t_cmd *cmd);

/* Free utils */

void		ft_free_cmds(t_cmd *list);
void		ft_free_cmd(t_cmd *cmd);
void		ft_free_redirs(t_redir *list);

/* Error utils */

int			ft_errmsg(char *msg);

/* Free utils (strarr) */

void		ft_free_strarr(char **arr);

/* Executor */

int			ft_executor(t_cmd *cmds, char **env);
void		ft_child(t_cmd *cmd, int input_fd, int pipe_fd[2], char **env);
int			ft_apply_redirs(t_redir *redirs);
int			ft_get_heredoc(char *limiter);
char		**ft_get_paths(char **env);
char		*ft_find_cmd_path(char *cmd, char **paths);

/* Global */

extern int	g_exit_code;

#endif