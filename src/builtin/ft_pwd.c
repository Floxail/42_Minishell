/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:39:44 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/31 14:38:01 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* print current pwd via getcwd */
int	ft_pwd(s_data *data)
{
	char	*buf[PATH_MAX];
	char	*ret;

	if (data->wd)
	{
		ft_putendl_fd(data->wd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	ret = getcwd(*buf, PATH_MAX);
	if (!ret)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(ret, STDOUT_FILENO);
}
