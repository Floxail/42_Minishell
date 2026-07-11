/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 11:57:48 by damarcin          #+#    #+#             */
/*   Updated: 2026/07/11 10:09:00 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_code(char *code)
{
	int	i;

	i = 0;
	while (code[i])
	{
		if (!isdigit(code[i])
			&& !(i == 0 && (code[i] == '+' || code[i] == '-')))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			return (0);
		}
		i++;
	}
	i = ft_atol(code);
	if (i > 2147483647)
	{
		ft_putstr_fd("minishell: exit: Illegal number: ", 2);
		ft_putstr_fd(code, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
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

//cleans up anything that might be allocated before exit
void	ft_exit(char *code, t_data *data, t_cmd *cmds)
{
	int	ex_code;

	if (!code)
		ex_code = 0;
	else if (is_valid_code(code))
		ex_code = ft_atoi(code);
	else
		return ;
	if (cmds)
	{
		ft_putstr_fd("exit\n", 1);
		ft_free_cmds(cmds);
		cleanup_data(data);
	}
	rl_clear_history();
	exit(ex_code % 256);
}
