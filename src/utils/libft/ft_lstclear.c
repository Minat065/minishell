/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:16:31 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 15:44:36 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
	*lst = NULL;
}

// void	del(void *content)
// {
// 	free(content);
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

// 	while (lst)
// 	{
// 		ft_printf("%s\n", (char *)lst->content);
// 		lst = lst->next;
// 	}

// 	ft_lstclear(&lst, del);

// 	ft_printf("After clear\n");
// 	ft_printf("lst: %s\n", (char *)lst);
// 	ft_printf("lst2: %s\n", (char *)lst2);
// 	ft_printf("lst3: %s\n", (char *)lst3);

// 	return (0);
// }