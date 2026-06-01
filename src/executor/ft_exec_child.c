/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/05/06 13:25:41 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}

int	ft_exec_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (ft_cd(&cmd->args[1], data));
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (ft_echo(&cmd->args[1]));
	if (!ft_strncmp(cmd->args[0], "env", 4))
		return (ft_env(data));
	if (!ft_strncmp(cmd->args[0], "exit", 5))
	{
		ft_exit(cmd->args[1], data);
		return (0);
	}
	if (!ft_strncmp(cmd->args[0], "export", 7))
		return (ft_export(&cmd->args[1], data));
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (ft_pwd(data));
	if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (ft_unset(&cmd->args[1], data));
	return (0);
}

static void	ft_exec_cmd(t_cmd *cmd, t_data *data)
{
	char	**paths;
	char	*cmd_path;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (ft_is_builtin(cmd->args[0]))
		exit(ft_exec_builtin(cmd, data));
	paths = ft_get_paths(data->env_vars);
	cmd_path = ft_find_cmd_path(cmd->args[0], paths);
	ft_free_strarr(paths);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(cmd_path, cmd->args, data->env_vars);
	free(cmd_path);
	ft_errmsg("execve");
	exit(1);
}

void	ft_child(t_cmd *cmd, int input_fd, int pipe_fd[2], t_data *data)
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
	ft_exec_cmd(cmd, data);
}
