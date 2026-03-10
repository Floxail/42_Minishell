/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:14:26 by damarcin          #+#    #+#             */
/*   Updated: 2026/03/10 12:30:19 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cleanup everything + exit
void exit_shell(void)
{
	rl_clear_history();
}

int	main()
{
	char	*line;
	
	set_sig_handlers();
	while (1)
	{
		line = readline(PRE);
		add_history(line);
		//line can be processed from here
	}
}