/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:09:46 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 15:44:36 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

// void	del(void *content)
// {
// 		free(content);
// }

// int	main(void)
// {
// 	t_list *lst;
// 	t_list *lst2;
// 	t_list *lst3;

// 	lst = ft_lstnew(strdup("Hello, World!"));
// 	lst2 = ft_lstnew(strdup("Hello, World!1"));
// 	lst3 = ft_lstnew(strdup("Hello, World!2"));

// 	lst->next = lst2;
// 	lst2->next = lst3;

// 	ft_lstdelone(lst2, del);

// 	while (lst)
// 	{
// 		ft_printf("%s\n", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }