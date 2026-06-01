/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 11:57:48 by damarcin          #+#    #+#             */
/*   Updated: 2026/05/13 16:31:34 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_code(char *code)
{
	int	i;

	i = 0;
	while (code[i])
	{
		if (!isdigit(code[i]) && !(i == 0 && code[i] == '+'))
			return (0);
		i++;
	}
	i = ft_atol(code);
	if (i < 0 || i > 2147483647)
		return (0);
	return (1);
}

/* free everything in data + the struct itself */
void	cleanup_data(t_data *data)
{
	if (data)
	{
		if (data->env_vars)
			free_env(data->env_vars);
		if (data->wd)
			free(data->wd);
		if (data->old_wd)
			free(data->old_wd);
		free(data);
	}
}

//add anything that needs cleaning up on exit here
void	ft_exit(char *code, t_data *data)
{
	int	ex_code;

	if (!code)
		ex_code = 0;
	else if (is_valid_code(code))
		ex_code = ft_atoi(code);
	else
	{
		ft_putstr_fd("sh: exit: Illegal number: ", 2);
		ft_putstr_fd(code, 2);
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	cleanup_data(data);
	rl_clear_history();
	exit (ex_code);
}
