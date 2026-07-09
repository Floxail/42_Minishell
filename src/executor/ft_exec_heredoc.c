/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by floxail           #+#    #+#             */
/*   Updated: 2026/07/09 11:40:23 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//assumes pointer is at dollar, returns 1 if dollar followed by nothing
int	dollar_len(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (i == 0)
		{
			if (str[i] == '_' || ft_isalpha(str[i]))
				i++;
			else
				break ;
		}
		else
		{
			if (ft_isalnum(str[i]))
				i++;
			else
				break ;
		}
	}
	return (i);
}

char	*replace_dollar(char *str, int start, t_data *data)
{
	char	*dollar_var;
	char	*rtn;
	char	*tmp;

	if (dollar_len(str + start) == 1)
		return (str);
	tmp = ft_substr(str, 0, start);
	dollar_var = ft_substr(str, start, dollar_len(str + start));
	if (get_var_val(data, &dollar_var[1]))
	{
		rtn = ft_strjoin(tmp, get_var_val(data, &dollar_var[1]));
		free(tmp);
		tmp = rtn;
		rtn = ft_strjoin(tmp, str + start + dollar_len(str + start));
	}
	else
		rtn = ft_strjoin(tmp, str + start + dollar_len(str + start));
	free(tmp);
	free(dollar_var);
	free(str);
	return (rtn);
}

char	*heredoc_expander(t_data *data, char *line)
{
	int	i;

	while (ft_strchr(line, '$'))
	{
		i = 0;
		while (line[i] != '$')
			i++;
		line = replace_dollar(line, i, data);
	}
	return (line);
}

int	ft_get_heredoc(char *limiter, t_data *data)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (ft_errmsg("pipe"), -1);
	while (1)
	{
		line = heredoc_expander(data, readline("heredoc> "));
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", 2);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
