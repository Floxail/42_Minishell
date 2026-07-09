/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/07/09 11:03:49 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	path_error(t_cmd *cmd, char *cmd_path)
{
	struct stat	buf;

	if (!cmd_path)
	{
		if (ft_strchr(cmd->args[0], 47))
			pcmderr(cmd->args[0], "No such file or directory");
		else
			pcmderr(cmd->args[0], "command not found");
		exit(127);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		pcmderr(cmd->args[0], "Permission denied");
		exit(126);
	}
	if (stat(cmd_path, &buf) == -1)
		exit(1);
	if (S_ISDIR(buf.st_mode))
	{
		pcmderr(cmd->args[0], "Is a directory");
		exit(126);
	}
}

int	ft_is_builtin(char *cmd)
{
	if (ft_strchr(cmd, '=') && var_name_valid(cmd))
		return (1);
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

int	ft_exec_builtin(t_cmd *cmd, t_data *data, t_cmd *cmd_list_start)
{
	if (ft_strchr(cmd->args[0], '=') && var_name_valid(cmd->args[0]))
		return (ft_export(&cmd->args[0], data));
	if (!ft_strncmp(cmd->args[0], "cd", 2))
		return (ft_cd(&cmd->args[1], data));
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		return (ft_echo(&cmd->args[1]));
	if (!ft_strncmp(cmd->args[0], "env", 3))
		return (ft_env(data));
	if (!ft_strncmp(cmd->args[0], "exit", 4))
	{
		if (cmd->args[1] && cmd->args[2])
		{
			pcmderr("exit", "too many arguments");
			return (1);
		}
		ft_exit(cmd->args[1], data, cmd_list_start);
		return (2);
	}
	if (!ft_strncmp(cmd->args[0], "export", 6))
		return (ft_export(&cmd->args[1], data));
	if (!ft_strncmp(cmd->args[0], "pwd", 3))
		return (ft_pwd(data));
	if (!ft_strncmp(cmd->args[0], "unset", 5))
		return (ft_unset(&cmd->args[1], data));
	return (0);
}

static void	ft_exec_cmd(t_cmd *cmd, t_data *data)
{
	char	**paths;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (ft_is_builtin(cmd->args[0]))
		exit(ft_exec_builtin(cmd, data, NULL));
	paths = ft_get_paths(data->env_vars);
	cmd->path = ft_find_cmd_path(cmd->args[0], paths);
	ft_free_strarr(paths);
	path_error(cmd, cmd->path);
	execve(cmd->path, cmd->args, data->env_vars);
	free(cmd->args[0]);
	ft_errmsg("execve");
	exit(errno);
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
	if (ft_apply_redirs(cmd->redirs, data) == -1)
		exit(1);
	ft_exec_cmd(cmd, data);
}
