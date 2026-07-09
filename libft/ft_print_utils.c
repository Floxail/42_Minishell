/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:52:27 by damarcin          #+#    #+#             */
/*   Updated: 2025/12/23 11:55:31 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_d(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_d(char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i += ft_putchar_d(c[i]);
	return (i);
}

int	ft_nb_len(int nbr)
{
	int	len;

	if (nbr == 0)
		return (1);
	len = 0;
	if (nbr < 0)
		len++;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}
