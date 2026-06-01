/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_open_redir(t_redir *r)
{
	if (r->type == TOKEN_REDIR_IN)
		return (open(r->file, O_RDONLY));
	if (r->type == TOKEN_REDIR_OUT)
		return (open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (r->type == TOKEN_APPEND)
		return (open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (ft_get_heredoc(r->file));
}

static int	ft_redir_target(t_redir *r)
{
	if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

int	ft_apply_redirs(t_redir *redirs)
{
	int	fd;

	while (redirs)
	{
		fd = ft_open_redir(redirs);
		if (fd == -1)
		{
			if (redirs->type != TOKEN_HEREDOC)
				ft_errmsg(redirs->file);
			return (-1);
		}
		dup2(fd, ft_redir_target(redirs));
		close(fd);
		redirs = redirs->next;
	}
	return (0);
}
