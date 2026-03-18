/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_executor(t_cmd *cmds, char **env)
{
	t_cmd	*cmd;
	int		input_fd;
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		last_status;

	cmd = cmds;
	input_fd = STDIN_FILENO;
	last_status = 0;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (ft_errmsg("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (ft_errmsg("fork"), 1);
		if (pid == 0)
			ft_child(cmd, input_fd, pipe_fd, env);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		last_status = status;
	if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (WEXITSTATUS(last_status));
}
