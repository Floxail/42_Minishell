/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:23:21 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:19:54 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* print everything within env_vars of a data struct */
int	ft_env(s_data *data)
{
	int	i;
	
	if (!data || !data->env_vars)
		return (1);
	i = 0;
	while (data->env_vars[i])
		ft_putendl_fd(data->env_vars[i++], STDOUT_FILENO);
	return (0);
}