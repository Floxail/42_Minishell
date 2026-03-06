/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/03 18:00:00 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	return (tok);
}

static t_token	*ft_token_last(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	ft_add_token(t_token **list, char *value, t_token_type type)
{
	t_token	*tok;
	t_token	*last;

	tok = ft_new_token(value, type);
	if (!tok)
		return (-1);
	last = ft_token_last(*list);
	if (!last)
		*list = tok;
	else
		last->next = tok;
	return (0);
}

void	ft_free_tokens(t_token *list)
{
	t_token	*next;

	while (list)
	{
		next = list->next;
		free(list->value);
		free(list);
		list = next;
	}
}
