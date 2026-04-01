/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:01:35 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:35:24 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* check if arg is a flag */
int	is_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] && ft_strncmp(arg[i], "-n", 2))
		return (1);
	return (0);
}

/* loop for printing out all args provided */
void	echo_print_args(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd (' ', STDOUT_FILENO);
		i++;
	}
}

/* checks for "-n" flag, prints out all args.
prints newline if "-n" was found */
int	ft_echo(char **args)
{
	int	n_flag;
	int	i;

	i = 0;
	n_flag = 0;
	if (args[i] && is_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	echo_print_args(args, i);
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
