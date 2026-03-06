/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/03/06 09:36:45 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

static int	ft_parse_step(t_cmd **cmds, t_cmd **cmd, t_token **tok)
{
	if ((*tok)->type == TOKEN_PIPE)
	{
		ft_cmd_addback(cmds, *cmd);
		*cmd = ft_new_cmd();
		if (!*cmd)
			return (-1);
		return (0);
	}
	if ((*tok)->type == TOKEN_WORD)
		return (ft_add_arg(*cmd, (*tok)->value));
	if (ft_add_redir(*cmd, (*tok)->type, (*tok)->next->value) == -1)
		return (-1);
	*tok = (*tok)->next;
	return (0);
}


t_cmd	*ft_parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*cmd;
	t_token	*tok;

	if (ft_check_syntax(tokens) == -1)
		return (NULL);
	cmds = NULL;
	cmd = ft_new_cmd();
	tok = tokens;
	while (tok && cmd)
	{
		if (ft_parse_step(&cmds, &cmd, &tok) == -1)
			return (ft_free_cmds(cmds), ft_free_cmd(cmd), NULL);
		tok = tok->next;
	}
	ft_cmd_addback(&cmds, cmd);
	return (cmds);
}
