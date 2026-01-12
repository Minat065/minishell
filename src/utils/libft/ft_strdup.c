/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 06:44:48 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 15:49:43 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = (char *)malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, ft_strlen(s1) + 1);
	return (ptr);
}

// #include <libc.h>
// #include "libft.h"

// int	main(void)
// {
// 	char *str = "Hello, World!";
// 	char *ptr;

// 	ptr = strdup(str);
// 	ft_printf("%s\n", ptr);
// 	free(ptr);

// 	ptr = ft_strdup(str);
// 	ft_printf("%s\n", ptr);
// 	free(ptr);

// 	return (0);
// }