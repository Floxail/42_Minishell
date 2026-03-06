/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/06 09:38:35 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static t_token_type	ft_get_op_type(char *input, int *i)
{
	if (input[*i] == '|')
		return (*i += 1, TOKEN_PIPE);
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (*i += 2, TOKEN_HEREDOC);
	if (input[*i] == '<')
		return (*i += 1, TOKEN_REDIR_IN);
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (*i += 2, TOKEN_APPEND);
	return (*i += 1, TOKEN_REDIR_OUT);
}


int	ft_extract_operator(t_lex_ctx *ctx)
{
	t_token_type	type;

	type = ft_get_op_type(ctx->input, &ctx->i);
	if (ft_add_token(&ctx->list, NULL, type) == -1)
		return (-1);
	return (0);
}
