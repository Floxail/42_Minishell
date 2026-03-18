/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_exec_cmd(t_cmd *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	paths = ft_get_paths(env);
	cmd_path = ft_find_cmd_path(cmd->args[0], paths);
	ft_free_strarr(paths);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(cmd_path, cmd->args, env);
	free(cmd_path);
	ft_errmsg("execve");
	exit(1);
}

void	ft_child(t_cmd *cmd, int input_fd, int pipe_fd[2], char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	if (ft_apply_redirs(cmd->redirs) == -1)
		exit(1);
	ft_exec_cmd(cmd, env);
}
