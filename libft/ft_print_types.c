/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:53:07 by damarcin          #+#    #+#             */
/*   Updated: 2025/12/19 14:11:42 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_d(int nbr)
{
	int	len;

	len = 0;
	if (nbr == -2147483647)
	{
		len += ft_putstr_d("-2");
		nbr = 147483647;
	}
	else if (nbr < 0)
	{
		len += ft_putchar_d('-');
		nbr *= -1;
	}
	if (nbr > 9)
	{
		len += ft_putnbr_d(nbr / 10);
		len += ft_putchar_d(nbr % 10 + '0');
	}
	else
		len += ft_putchar_d(nbr % 10 + '0');
	return (len);
}

int	ft_print_ptr(uintptr_t nbr)
{
	int		len;
	char	*base;

	base = "0123456789abcdef";
	len = ft_putstr_d("0x");
	if (nbr == 0)
		return (len + ft_putchar_d('0'));
	if (nbr > 15)
	{
		len += ft_print_ptr(nbr / 16);
		len += ft_putchar_d(base[nbr % 16]);
	}
	else
		len += ft_putchar_d(base[nbr % 16]);
	return (len);
}

int	ft_print_base(long nb, char *base)
{
	int	len;
	int	baselen;

	len = 0;
	baselen = ft_strlen(base);
	if (nb == 0)
		return (ft_putchar_d(base[0]));
	if (nb < 0)
	{
		len += ft_putchar_d('-');
		nb *= -1;
	}
	if (nb > baselen)
	{
		len += ft_print_base(nb / 10, base);
		len += ft_putchar_d(base[nb % baselen]);
	}
	else
		len += ft_putchar_d(base[nb % baselen]);
	return (len);
}

int	ft_print_unsigned(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (ft_putchar_d('0'));
	if (nbr > 9)
	{
		len += ft_print_unsigned(nbr / 10);
		len += ft_putchar_d(nbr % 10 + '0');
	}
	else
		len += ft_putchar_d(nbr % 10 + '0');
	return (len);
}
