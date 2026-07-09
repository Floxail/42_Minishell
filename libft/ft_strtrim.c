/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:35:02 by damarcin          #+#    #+#             */
/*   Updated: 2025/10/10 11:34:10 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set [i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rtn;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && isinset(s1[start], (char *)set))
		start++;
	while (start < end && s1[end] && isinset(s1[end], (char *)set))
		end--;
	rtn = ft_substr(s1 + start, 0, (size_t)(end - start + 1));
	return (rtn);
}
