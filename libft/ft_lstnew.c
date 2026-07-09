/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:55:00 by damarcin          #+#    #+#             */
/*   Updated: 2025/10/13 14:01:51 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*rtn;

	rtn = malloc(sizeof(t_list));
	if (!rtn)
		return (NULL);
	rtn->content = content;
	rtn->next = NULL;
	return (rtn);
}
