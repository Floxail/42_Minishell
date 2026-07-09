/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:59:05 by damarcin          #+#    #+#             */
/*   Updated: 2025/09/30 14:15:04 by damarcin         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(dst);
	if (j < size && size > 0)
	{
		while (i + j < size - 1 && src[i])
		{
			dst[j + i] = src[i];
			i++;
		}
	}
	dst[j + i] = '\0';
	if (j > size)
		return (size + ft_strlen(src));
	else
		return (j + ft_strlen(src));
}
