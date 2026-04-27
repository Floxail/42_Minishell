/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 11:57:48 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:36:02 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* free everything in data + the struct itself */
void	cleanup_data(s_data *data)
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
void	ft_exit(s_data *data)
{
	cleanup_data(data);
	rl_clear_history();
	exit(0);
}
