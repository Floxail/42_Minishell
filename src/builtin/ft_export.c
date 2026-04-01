/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:54:16 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:35:53 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/* check if the provided string starts with a valid var name followed by '=' */
int	invalid_env_var_name(char *var)
{
	if (!var || !var[0])
		return (EXIT_FAILURE);
	if (!ft_strchr(var, '='))
		return (EXIT_FAILURE);
	if (!var_name_valid(var))
	{
		ft_putstr_fd("export: bad variable name\n", STDERR_FILENO); //bad var name err msg
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_export(char **args, s_data *data)
{
	int	i;
	int	j;

	j = 0;
	if (!args)
		return (EXIT_FAILURE);
	while (args[j])
	{
		if (invalid_env_var_name(args[j]))
			return (EXIT_FAILURE);
		if (env_add_replace_var(data, args[j++]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
