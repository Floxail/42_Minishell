/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errmsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/06/15 13:14:30 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pcmderr(char *cmd, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_errmsg(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}
