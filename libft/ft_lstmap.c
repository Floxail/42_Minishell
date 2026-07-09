/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damarcin <damarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:26:23 by damarcin          #+#    #+#             */
/*   Updated: 2025/10/14 11:40:23 by damarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rtn;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	rtn = NULL;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&rtn, del);
			return (NULL);
		}
		ft_lstadd_back(&rtn, tmp);
		lst = lst->next;
	}
	return (rtn);
}
