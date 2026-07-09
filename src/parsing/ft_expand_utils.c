/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/06 09:57:55 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_var_name(char *str, int *i)
{
	int	start;

	if (str[*i] == '?')
		return (*i += 1, ft_strdup("?"));
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	return (ft_substr(str, start, *i - start));
}

char	*ft_get_var_val(char *name, char **env, int code)
{
	int		i;
	size_t	len;

	if (!name || !*name)
		return (ft_strdup("$"));
	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(code));
	i = 0;
	len = ft_strlen(name);
	while (env && env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	ft_exp_char(t_exp_ctx *ctx)
{
	char	tmp[2];
	char	*new;

	tmp[0] = ctx->src[ctx->i++];
	tmp[1] = '\0';
	new = ft_strjoin(ctx->result, tmp);
	free(ctx->result);
	ctx->result = new;
}

void	ft_exp_tilde(t_exp_ctx *ctx, char **env, int code)
{
	char	*home;
	char	*new;

	ctx->i++;
	home = ft_get_var_val("HOME", env, code);
	new = ft_strjoin(ctx->result, home);
	free(home);
	free(ctx->result);
	ctx->result = new;
}

void	ft_exp_dq_literal(t_exp_ctx *ctx)
{
	char	tmp[2];
	char	*new;

	ctx->i += 2;
	tmp[1] = '\0';
	while (ctx->src[ctx->i] && ctx->src[ctx->i] != '"')
	{
		tmp[0] = ctx->src[ctx->i++];
		new = ft_strjoin(ctx->result, tmp);
		free(ctx->result);
		ctx->result = new;
	}
	if (ctx->src[ctx->i] == '"')
		ctx->i++;
}
