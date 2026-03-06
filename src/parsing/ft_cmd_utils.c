/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/06 09:58:48 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_new_cmd(void)
{
	return (ft_calloc(1, sizeof(t_cmd)));
}

int	ft_add_arg(t_cmd *cmd, char *val)
{
	char	**new_args;
	int		i;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = ft_calloc(i + 2, sizeof(char *));
	if (!new_args)
		return (-1);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(val);
	free(cmd->args);
	cmd->args = new_args;
	return (0);
}

static t_cmd	*ft_cmd_last(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_cmd_addback(t_cmd **list, t_cmd *cmd)
{
	t_cmd	*last;

	if (!*list)
	{
		*list = cmd;
		return ;
	}
	last = ft_cmd_last(*list);
	last->next = cmd;
}
