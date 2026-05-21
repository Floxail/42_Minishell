/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:40:45 by damarcin          #+#    #+#             */
/*   Updated: 2026/04/30 13:16:30 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* returns number of vars in env (excluding final null var) */
int	env_len(char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}

/* duplicate a full env array (deep copy) */
char	**env_dup(char **env)
{
	char	**dup;
	int		len;
	int		i;

	len = env_len(env);
	dup = malloc(sizeof(char *) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = ft_strdup(env[i]);
		if (!dup[i])
		{
			dup[i] = NULL;
			free_env(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

/* init shell data: duplicate env, get working directory */
t_data	*init_data(char **env)
{
	t_data	*data;
	char	buf[PATH_MAX];

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->old_wd = NULL;
	data->env_vars = env_dup(env);
	data->wd = ft_strdup(getcwd(buf, PATH_MAX));
	if (!data->env_vars || !data->wd)
	{
		cleanup_data(data);
		return (NULL);
	}
	return (data);
}

/* free each var in env, then free env */
void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
