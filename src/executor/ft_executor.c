/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/05/06 13:39:51 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_wait_last(void)
{
	int	status;
	int	last;

	last = 0;
	while (waitpid(-1, &status, 0) > 0)
		last = status;
	if (WIFSIGNALED(last))
		return (128 + WTERMSIG(last));
	return (WEXITSTATUS(last));
}

static int	ft_exec_step(t_cmd *cmd, int *input_fd, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (cmd->next && pipe(pipe_fd) == -1)
		return (ft_errmsg("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (ft_errmsg("fork"), -1);
	if (pid == 0)
		ft_child(cmd, *input_fd, pipe_fd, data);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	return (0);
}

int	ft_executor(t_cmd *cmds, t_data *data)
{
	t_cmd	*cmd;
	int		input_fd;

	cmd = cmds;
	if (!cmd->next && !cmd->redirs && cmd->args && cmd->args[0]
		&& ft_is_builtin(cmd->args[0]))
		return (ft_exec_builtin(cmd, data));
	input_fd = STDIN_FILENO;
	while (cmd)
	{
		if (ft_exec_step(cmd, &input_fd, data) == -1)
			return (1);
		cmd = cmd->next;
	}
	return (ft_wait_last());
}
