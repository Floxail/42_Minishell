/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/03 18:00:00 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_free_redirs(t_redir *list)
{
	t_redir	*next;

	while (list)
	{
		next = list->next;
		free(list->file);
		free(list);
		list = next;
	}
}

static void	ft_free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_free_args(cmd->args);
	ft_free_redirs(cmd->redirs);
	free(cmd);
}

void	ft_free_cmds(t_cmd *list)
{
	t_cmd	*next;

	while (list)
	{
		next = list->next;
		ft_free_cmd(list);
		list = next;
	}
}
