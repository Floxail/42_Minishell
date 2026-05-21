/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:14:26 by damarcin          #+#    #+#             */
/*   Updated: 2026/05/06 13:40:56 by damarcin         ###   ########.fr       */
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

static void	ft_loop(t_data *data)
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
			if (!ft_strncmp(line, "exit", 4))
				ft_exit(0, data);
			add_history(line);
			run_line(line, data);
		}
		free(line);
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
