/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:49:14 by damarcin          #+#    #+#             */
/*   Updated: 2025/12/23 11:54:54 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	parse_flag(va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar_d(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr_d(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(args, uintptr_t)));
	else if (c == 'd')
		return (ft_putnbr_d(va_arg(args, int)));
	else if (c == 'i')
		return (ft_putnbr_d(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_unsigned(va_arg(args, uint)));
	else if (c == 'x')
		return (ft_print_base(va_arg(args, long), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_print_base(va_arg(args, long), "0123456789ABCDEF"));
	else if (c == '%')
		return (ft_putchar_d(c));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i])
			{
				len += parse_flag(args, str[i++]);
			}
		}
		else
			len += ft_putchar_d(str[i++]);
	}
	va_end(args);
	return (len);
}
