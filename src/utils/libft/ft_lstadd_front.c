/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:49:11 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 15:44:36 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	t_list	*new;
// 	t_list	*new2;
// 	t_list	*new3;
// 	t_list	*head;

// 	head = NULL;
// 	new = ft_lstnew("new");
// 	new2 = ft_lstnew("new2");
// 	new3 = ft_lstnew("new3");
// 	ft_lstadd_front(&head, new);
// 	ft_printf("part1\n");
// 	ft_printf("head->content: %s\n", head->content);
// 	ft_printf("head->next: %p\n", head->next);
// 	ft_lstadd_front(&head, new2);
// 	ft_printf("part2\n");
// 	ft_printf("head->content: %s\n", head->content);
// 	ft_printf("head->next->content: %s\n", head->next->content);
// 	ft_printf("head->next: %p\n", head->next);
// 	ft_printf("head->next->next: %p\n", head->next->next);
// 	ft_lstadd_front(&head, new3);
// 	ft_printf("part3\n");
// 	ft_printf("head->content: %s\n", head->content);
// 	ft_printf("head->next->content: %s\n", head->next->content);
// 	ft_printf("head->next->next->content: %s\n", head->next->next->content);
// 	ft_printf("head->next: %p\n", head->next);
// 	ft_printf("head->next->next: %p\n", head->next->next);
// 	ft_printf("head->next->next->next: %p\n", head->next->next->next);
// 	return (0);
// }
