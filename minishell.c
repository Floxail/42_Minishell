/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:14:26 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/05 13:29:39 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	exit_shell(void)
{
	rl_clear_history();
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
	}
	else if (signal == SIGQUIT)
	{
		return ;
	}
}

int	main(void)
{
	char	*line;

	signal(SIGINT, sig_handler);
	while (1)
	{
		line = readline("$>");
		if (!line)
			break ;
		ft_printf("line read: %s\n", line);
		add_history(line);
		free(line);
	}
	exit_shell();
}
