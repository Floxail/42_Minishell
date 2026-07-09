/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:14:06 by damarcin          #+#    #+#             */
/*   Updated: 2025/10/13 14:28:58 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	if (!lst)
		return (i);
	else
		i++;
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
