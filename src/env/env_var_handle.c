/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:46:32 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:35:06 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* append a new var to env_vars. assumes var to be correctly formatted */
int	env_add_var(s_data *data, char *var)
{
	int		len;
	char	**rtn;
	int		i;

	len = env_len(data->env_vars);
	rtn = malloc(sizeof(char *) * (len + 2));
	if (!rtn)
		return (EXIT_FAILURE);
	i = 0;
	while (data->env_vars[i])
	{
		rtn[i] = data->env_vars[i];
		i++;
	}
	rtn[i++] = ft_strdup(var);
	rtn[i] = NULL;
	free(data->env_vars);
	data->env_vars = rtn;
	return (EXIT_SUCCESS);
}

/* same as env_add_var but also checks if var already exists in env.
replaces the value of var if it already exists in env,
appends var to env otherwise */
int	env_add_replace_var(s_data *data, char *var)
{
	int	i;

	i = 0;
	if (env_contains(data->env_vars, var))
	{
		while (!cmp_var_name(var, data->env_vars[i]))
			i++;
		free(data->env_vars[i]);
		data->env_vars[i] = ft_strdup(var);
		if (data->env_vars[i])
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE); //mem error
	}
	else
		return (env_add_var(data, var));
}

/* remove var from env. 
requires a full env realloc since env has to be a char** */
int	env_rm_var(s_data *data, char *var_name)
{
	int		i;
	int		j;
	char	**rtn;

	if (!env_contains(data->env_vars, var_name))
		return (EXIT_SUCCESS); //var not found, not treated as error
	rtn = malloc(sizeof(char *) * (env_len(data->env_vars)));
	if (!rtn)
		return (EXIT_FAILURE); //mem error
	i = 0;
	j = 0;
	while (data->env_vars[i])
	{
		if (!cmp_var_name(var_name, data->env_vars[i]))
			rtn[j++] = data->env_vars[i++];
		else
			free(data->env_vars[i++]);
	}
	rtn[j] = NULL;
	free(data->env_vars);
	data->env_vars = rtn;
	return (EXIT_SUCCESS);
}
