/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:34:18 by damarcin          #+#    #+#             */
/*   Updated: 2026/02/12 14:53:42 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *str, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			words++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (words);
}

static char	**cleanup(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static int	wordlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**rtn;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	rtn = malloc (sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!rtn)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			rtn[i] = ft_substr(s, 0, wordlen(s, c));
			if (!rtn[i])
				return (cleanup(rtn, i));
			s += wordlen(s, c);
			i++;
		}
	}
	rtn[i] = NULL;
	return (rtn);
}
