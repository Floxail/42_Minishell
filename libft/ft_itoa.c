/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:39:04 by damarcin          #+#    #+#             */
/*   Updated: 2025/10/13 13:26:41 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findpow(int n)
{
	int	pow;

	if (n == 0)
		return (1);
	pow = 0;
	if (n < 0)
		pow++;
	while (n)
	{
		pow++;
		n /= 10;
	}
	return (pow);
}

char	*ft_itoa(int n)
{
	int		pow;
	char	*rtn;

	pow = ft_findpow(n);
	rtn = malloc(sizeof(char) * (pow + 1));
	if (!rtn)
		return (NULL);
	if (n == 0)
		rtn[0] = '0';
	if (n < 0)
		rtn[0] = '-';
	rtn[pow] = '\0';
	while (n)
	{
		if (n < 0)
			rtn[--pow] = (n % 10) * -1 + '0';
		else
			rtn[--pow] = (n % 10) + '0';
		n /= 10;
	}
	return (rtn);
}
