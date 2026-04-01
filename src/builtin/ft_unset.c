/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:27:03 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:35:18 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* returns success if unset or if var not found */
int	ft_unset(char **args, s_data *data)
{
	int	i;

	if (!args || !args[0])
		return (EXIT_SUCCESS);
	i = 0;
	while (args[i])
	{
		if (env_rm_var(data, args[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
