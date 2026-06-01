/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/06 10:12:14 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_init_exp_ctx(t_exp_ctx *ctx, char *src)
{
	ctx->src = src;
	ctx->i = 0;
	ctx->in_sq = 0;
	ctx->in_dq = 0;
	ctx->result = ft_calloc(1, 1);
}

static void	ft_exp_dollar(t_exp_ctx *ctx, char **env, int code)
{
	char	*name;
	char	*tmp;

	ctx->i++;
	name = ft_get_var_name(ctx->src, &ctx->i);
	tmp = ft_get_var_val(name, env, code);
	free(name);
	if (tmp)
		name = ft_strjoin(ctx->result, tmp);
	else
		name = ft_strjoin(ctx->result, "");
	free(tmp);
	free(ctx->result);
	ctx->result = name;
}

static void	ft_exp_step(t_exp_ctx *ctx, char **env, int code)
{
	if (ctx->src[ctx->i] == '\'' && !ctx->in_dq)
	{
		ctx->in_sq = !ctx->in_sq;
		ctx->i++;
	}
	else if (ctx->src[ctx->i] == '"' && !ctx->in_sq)
	{
		ctx->in_dq = !ctx->in_dq;
		ctx->i++;
	}
	else if (ctx->src[ctx->i] == '$' && !ctx->in_sq)
	{
		if (ctx->src[ctx->i + 1] == '"')
			ft_exp_dq_literal(ctx);
		else
			ft_exp_dollar(ctx, env, code);
	}
	else
		ft_exp_char(ctx);
}

char	*ft_expand_value(char *src, char **env, int code)
{
	t_exp_ctx	ctx;

	ft_init_exp_ctx(&ctx, src);
	if (src[0] == '~' && (src[1] == '/' || src[1] == '\0'))
		ft_exp_tilde(&ctx, env, code);
	while (ctx.src[ctx.i])
		ft_exp_step(&ctx, env, code);
	return (ctx.result);
}

void	ft_expander(t_token *tokens, char **env, int code)
{
	t_token	*tok;
	char	*val;

	tok = tokens;
	while (tok)
	{
		if (tok->type == TOKEN_WORD)
		{
			val = ft_expand_value(tok->value, env, code);
			if (val)
			{
				free(tok->value);
				tok->value = val;
			}
		}
		tok = tok->next;
	}
}
