/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_handle_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:48:55 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:34:23 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* compare var names.
src can be a var name or a full var string
dst has to be a full var string */
int	cmp_var_name(char *src, char *dst)
{
	int	i;

	i = 0;
	while (src[i] && dst[i] && src[i] == dst[i])
	{
		if (src[i] == '=' && dst[i] == '=')
			return (1);
		i++;
	}
	if (!src[i] && dst[i] && dst[i] == '=')
		return (1);
	else
		return (0);
}

/* checks if a var exists in env. 
works with either var name or full var string with same var name
returns 1 if var found, 0 if not found */
int	env_contains(char **env, char *var_name)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (cmp_var_name(var_name, env[i]))
			return (1);
		i++;
	}
	return (0);
}

/* returns pointer to 1st char after '=' in a var string 
returns null if var not found */
char	*get_var_val(s_data *data, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (data->env_vars[i])
	{
		j = 0;
		while (data->env_vars[i][j] && var[j]
			&& data->env_vars[i][j] == var[j])
			j++;
		if (data->env_vars[i][j] == '=' && !var[j])
			return (&data->env_vars[i][j + 1]);
		i++;
	}
	return (NULL);
}

//assumes var string contains = sign, this should be checked earlier
int	var_name_valid(char *var)
{
	int	i;

	i = 0;
	if (!isalpha(var[i]) && var[i] != '_')
		return (0); //bad var name
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!isalnum(var[i]) && var[i] != '_')
			return (0); //bad var name
		i++;
	}
	return (1);
}
