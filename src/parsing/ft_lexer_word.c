/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/06 10:12:06 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** ft_word_end : renvoie 1 si le caractère courant termine le mot.
** Un mot se termine sur : fin de chaîne, espace hors-quotes,
** ou métacaractère hors-quotes.
*/
static int	ft_word_end(t_lex_ctx *ctx)
{
	char	c;

	c = ctx->input[ctx->i];
	return (!c || ((ft_isspace(c) || ft_is_meta(c))
			&& !ctx->in_sq && !ctx->in_dq));
}

/*
** ft_update_quote : bascule l'état des quotes en lisant le caractère courant.
** La quote lue N'EST PAS ajoutée au token (elle est consommée silencieusement).
** Règle : un ' à l'intérieur de "..." est littéral, et vice versa.
*/
static void	ft_update_quote(t_lex_ctx *ctx, char c)
{
	if (c == '\'' && !ctx->in_dq)
		ctx->in_sq = !ctx->in_sq;
	else if (c == '"' && !ctx->in_sq)
		ctx->in_dq = !ctx->in_dq;
}

/*
** ft_scan_word : avance ctx->i jusqu'à la fin du mot.
** Met à jour les états de quotes au passage.
** Renvoie l'index de début du mot.
*/
static int	ft_scan_word(t_lex_ctx *ctx)
{
	int	start;

	start = ctx->i;
	while (!ft_word_end(ctx))
	{
		ft_update_quote(ctx, ctx->input[ctx->i]);
		ctx->i++;
	}
	return (start);
}

/*
** ft_extract_word : extrait un token WORD depuis ctx->input[ctx->i].
** La valeur conserve les quotes (ex: "hello world" → `"hello world"`).
** L'Expander les retraitera pour les supprimer et développer les variables.
*/
int	ft_extract_word(t_lex_ctx *ctx)
{
	int		start;
	char	*value;

	start = ft_scan_word(ctx);
	value = ft_substr(ctx->input, start, ctx->i - start);
	if (!value)
		return (-1);
	if (ft_add_token(&ctx->list, value, TOKEN_WORD) == -1)
		return (free(value), -1);
	return (0);
}
