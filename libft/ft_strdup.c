/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:29:31 by damarcin          #+#    #+#             */
/*   Updated: 2025/10/10 11:37:47 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*rtn;
	int		i;

	i = 0;
	rtn = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!rtn)
		return (NULL);
	while (s[i])
	{
		rtn[i] = s[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
