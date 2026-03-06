/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/05 10:48:37 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	ft_init_ctx(t_lex_ctx *ctx, char *input)
{
	ctx->input = input;
	ctx->i = 0;
	ctx->in_sq = 0;
	ctx->in_dq = 0;
	ctx->list = NULL;
}

static int	ft_lex_step(t_lex_ctx *ctx)
{
	char	c;

	c = ctx->input[ctx->i];
	if (ft_isspace(c) && !ctx->in_sq && !ctx->in_dq)
	{
		ctx->i++;
		return (0);
	}
	if (ft_is_meta(c) && !ctx->in_sq && !ctx->in_dq)
		return (ft_extract_operator(ctx));
	return (ft_extract_word(ctx));
}

t_token	*ft_lexer(char *input)
{
	t_lex_ctx	ctx;

	ft_init_ctx(&ctx, input);
	while (ctx.input[ctx.i])
	{
		if (ft_lex_step(&ctx) == -1)
			return (ft_free_tokens(ctx.list), NULL);
	}
	if (ctx.in_sq || ctx.in_dq)
		return (ft_errmsg("syntax error: unclosed quote"),
			ft_free_tokens(ctx.list), NULL);
	return (ctx.list);
}
