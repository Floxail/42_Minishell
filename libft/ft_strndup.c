/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:05:09 by damarcin          #+#    #+#             */
/*   Updated: 2026/07/09 11:40:48 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int len)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!str || len <= 0)
		return (NULL);
	rtn = malloc(sizeof(char) * (len + 1));
	if (!rtn)
		return (NULL);
	while (str[i] && i < len)
	{
		rtn[i] = str[i];
		i++;
	}
	while (i <= len)
	{
		rtn[i] = '\0';
		i++;
	}
	return (rtn);
}
