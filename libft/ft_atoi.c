/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:41:12 by damarcin          #+#    #+#             */
/*   Updated: 2026/02/13 13:58:11 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	rtn;
	int	mult;

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
