/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/03 18:00:00 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static t_redir	*ft_new_redir(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (free(redir), NULL);
	return (redir);
}

static t_redir	*ft_redir_last(t_redir *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	ft_add_redir(t_cmd *cmd, t_token_type type, char *file)
{
	t_redir	*redir;
	t_redir	*last;

	redir = ft_new_redir(type, file);
	if (!redir)
		return (-1);
	last = ft_redir_last(cmd->redirs);
	if (!last)
		cmd->redirs = redir;
	else
		last->next = redir;
	return (0);
}
