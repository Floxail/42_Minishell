/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:23:21 by damarcin          #+#    #+#             */
/*   Updated: 2026/05/13 16:45:36 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* print everything within env_vars of a data struct */
int	ft_env(t_data *data)
{
	int	i;

	if (!data || !data->env_vars)
		return (1);
	i = 0;
	while (data->env_vars[i])
		ft_putendl_fd(data->env_vars[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
