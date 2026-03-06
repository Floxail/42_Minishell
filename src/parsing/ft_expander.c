/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/06 09:58:03 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static void	ft_init_exp_ctx(t_exp_ctx *ctx, char *src)
{
	ctx->src = src;
	ctx->i = 0;
	ctx->in_sq = 0;
	ctx->in_dq = 0;
	ctx->result = ft_calloc(1, 1);
}

static void	ft_exp_char(t_exp_ctx *ctx)
{
	char	tmp[2];
	char	*new_res;

	tmp[0] = ctx->src[ctx->i++];
	tmp[1] = '\0';
	new_res = ft_strjoin(ctx->result, tmp);
	free(ctx->result);
	ctx->result = new_res;
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

char	*ft_expand_value(char *src, char **env, int code)
{
	t_exp_ctx	ctx;

	ft_init_exp_ctx(&ctx, src);
	while (ctx.src[ctx.i])
	{
		if (ctx.src[ctx.i] == '\'' && !ctx.in_dq)
		{
			ctx.in_sq = !ctx.in_sq;
			ctx.i++;
		}
		else if (ctx.src[ctx.i] == '"' && !ctx.in_sq)
		{
			ctx.in_dq = !ctx.in_dq;
			ctx.i++;
		}
		else if (ctx.src[ctx.i] == '$' && !ctx.in_sq)
			ft_exp_dollar(&ctx, env, code);
		else
			ft_exp_char(&ctx);
	}
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
