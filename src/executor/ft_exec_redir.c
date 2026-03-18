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

int	ft_apply_redirs(t_redir *redirs)
{
	int	fd;

	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_IN)
		{
			fd = open(redirs->file, O_RDONLY);
			if (fd == -1)
				return (ft_errmsg(redirs->file), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == TOKEN_REDIR_OUT)
		{
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (ft_errmsg(redirs->file), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->type == TOKEN_APPEND)
		{
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (ft_errmsg(redirs->file), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->type == TOKEN_HEREDOC)
		{
			fd = ft_get_heredoc(redirs->file);
			if (fd == -1)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redirs = redirs->next;
	}
	return (0);
}
