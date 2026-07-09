/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:42:17 by damarcin          #+#    #+#             */
/*   Updated: 2025/10/13 12:46:38 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*rtn;

	rtn = ft_strdup(s);
	if (!rtn)
		return (NULL);
	i = 0;
	while (rtn[i])
	{
		rtn[i] = (*f)(i, s[i]);
		i++;
	}
	return (rtn);
}
