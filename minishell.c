/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:14:26 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:02:19 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
	}
	else if (signal == SIGQUIT)
	{
		return ;
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	s_data *data;
	char	**args;

	data = malloc(sizeof(s_data));
	data->wd = NULL;
	data->old_wd = NULL;
	data->env_vars = ft_split("", ' ');

	args = ft_split("src", ' ');
	ft_cd(args, data);
	if (data->wd)
		ft_putendl_fd(data->wd, STDOUT_FILENO);
	ft_putendl_fd("env:", STDOUT_FILENO);
	ft_env(data);
	write(1, "\n", 1);
	free_env(args);

	args = ft_split("../", ' ');
	ft_cd(args, data);
	ft_putendl_fd("vars:", STDOUT_FILENO);
	ft_putendl_fd(data->wd, STDOUT_FILENO);
	ft_putendl_fd(data->old_wd, STDOUT_FILENO);
	ft_putendl_fd("env:", STDOUT_FILENO);
	ft_env(data);
	write(1, "\n", 1);
	free_env(args);

	args = ft_split("/", ' ');
	ft_cd(args, data);
	ft_putendl_fd("vars:", STDOUT_FILENO);
	ft_putendl_fd(data->wd, STDOUT_FILENO);
	ft_putendl_fd(data->old_wd, STDOUT_FILENO);
	ft_putendl_fd("env:", STDOUT_FILENO);
	ft_env(data);
	write(1, "\n", 1);
	free_env(args);


	args = ft_split("test=1", ' ');
	ft_export(args, data);
	ft_env(data);
	free_env(args);

	args = ft_split("test2=2 test123=54 testttt=abccc", ' ');
	ft_export(args, data);
	ft_env(data);
	free_env(args);
	
	free_env(data->env_vars);
	free(data->wd);
	free(data->old_wd);
	free(data);
}
