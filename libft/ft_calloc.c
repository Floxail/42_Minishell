/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:16:09 by damarcin          #+#    #+#             */
/*   Updated: 2025/10/07 16:59:42 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*rtn;

	rtn = malloc(nmemb * size);
	if (!rtn)
		return (NULL);
	ft_bzero(rtn, nmemb * size);
	return (rtn);
}
