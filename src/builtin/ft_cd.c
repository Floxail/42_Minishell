/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:46:46 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:37:47 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* update path variables in data and their corresponding env vars*/
int	update_paths(s_data *data, char *path)
{
	char	*tmp;

	if (data->wd)
	{
		if (data->old_wd)
			free(data->old_wd);
		data->old_wd = ft_strdup(data->wd);
		tmp = ft_strjoin("OLDPWD=", data->wd);
		env_add_replace_var(data, tmp);
		free(tmp);
		free(data->wd);
	}
	data->wd = ft_strdup(path);
	tmp = ft_strjoin("PWD=", path);
	env_add_replace_var(data, tmp);
	free(tmp);
	return (EXIT_SUCCESS);
}

/* calls update_paths if chdir check passes, returns error otherwise */
int	change_dir(s_data *data, char *path)
{
	char	buf[PATH_MAX];

	if (chdir(path) == EXIT_SUCCESS)
		return (update_paths(data, getcwd(buf, PATH_MAX)));
	else
	{
		ft_putendl_fd("cd: cannot access directory.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
}

int	ft_cd(char **args, s_data *data)
{
	int	ret;

	ret = EXIT_FAILURE;
	if (!args || !args[0][0])
		return (EXIT_SUCCESS);
	if (args[1])
	{
		ft_putendl_fd("Error: too many arguments.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (ft_strncmp("-", args[0], 2) == 0)
	{
		if (env_contains(data->env_vars, "OLDPWD"))
		{
			if (change_dir(data, get_var_val(data, "OLDPWD")) == EXIT_SUCCESS)
				ft_putendl_fd(data->wd, STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
		else
		{
			ft_putendl_fd(data->wd, STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
	}
	return (change_dir(data, args[0]));
}
