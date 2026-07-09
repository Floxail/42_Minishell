/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:14:26 by damarcin          #+#    #+#             */
/*   Updated: 2026/06/16 11:39:54 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static void	run_line(char *line, t_data *data)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = ft_lexer(line);
	if (!tokens)
		return ;
	ft_expander(tokens, data->env_vars, g_exit_code);
	cmds = ft_parser(tokens);
	ft_free_tokens(tokens);
	if (!cmds)
		return ;
	g_exit_code = ft_executor(cmds, data);
	ft_free_cmds(cmds);
}

static void	ft_process_line(char *line, int interactive, t_data *data)
{
	if (*line)
	{
		if (interactive)
			add_history(line);
		run_line(line, data);
	}
	free(line);
}

static char	*ft_read_line(void)
{
	char	*line;
	size_t	n;
	size_t	len;

	line = NULL;
	n = 0;
	if (getline(&line, &n, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static void	ft_loop(t_data *data)
{
	char	*line;
	int		interactive;

	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		if (interactive)
			line = readline(PROMPT);
		else
			line = ft_read_line();
		if (!line)
		{
			if (interactive)
				ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		ft_process_line(line, interactive, data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = init_data(env);
	if (!data)
		return (1);
	set_sig_handlers();
	ft_loop(data);
	cleanup_data(data);
	rl_clear_history();
	return (g_exit_code);
}
