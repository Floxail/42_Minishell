/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/06 09:36:55 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_is_redir(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

int	ft_check_syntax(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == TOKEN_PIPE)
		return (ft_errmsg("syntax error near unexpected token `|'"));
	while (tok)
	{
		if (tok->type == TOKEN_PIPE
			&& (!tok->next || tok->next->type == TOKEN_PIPE))
			return (ft_errmsg("syntax error near unexpected token `|'"));
		if (ft_is_redir(tok->type)
			&& (!tok->next || tok->next->type != TOKEN_WORD))
			return (ft_errmsg("syntax error near unexpected token `newline'"));
		tok = tok->next;
	}
	return (0);
}
