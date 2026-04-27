/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:14:26 by damarcin          #+#    #+#             */
/*   Updated: 2026/04/27 00:00:00 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static void	run_line(char *line, s_data *data)
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
	g_exit_code = ft_executor(cmds, data->env_vars);
	ft_free_cmds(cmds);
}

static void	ft_loop(s_data *data)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (*line)
		{
			add_history(line);
			run_line(line, data);
		}
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	s_data	*data;

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
