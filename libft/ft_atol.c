/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:44:05 by damarcin          #+#    #+#             */
/*   Updated: 2026/02/13 14:13:47 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	rtn;
	int		mult;

	i = 0;
	mult = 1;
	rtn = 0;
	while (nptr[i] && (nptr[i] == 32 || (nptr[i] < 14 && nptr[i] > 8)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			mult *= -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		rtn = (rtn * 10) + (nptr[i] - '0');
		i++;
	}
	return (rtn * mult);
}
