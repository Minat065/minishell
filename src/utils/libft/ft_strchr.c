/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 03:36:54 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 15:49:43 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (c > 127)
		c -= 128;
	while (c < 0)
		c += 128;
	if (c < 0 || c > 127)
		return ((char *)s);
	if (c == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

// #include "libft.h"
// #include <string.h>

// int	main(void)
// {
// 	char *s = "libft-test-tokyo";
// 	ft_printf("ft_strchr: %s\n", ft_strchr(s, 'l' + 516));
// 	ft_printf("strchr: %s\n", strchr(s, 'l' + 516));
// 	ft_printf("ft_strchr: %s\n", ft_strchr(s, 'b' + 516));
// 	ft_printf("strchr: %s\n", strchr(s, 'b' + 516));
// 	ft_printf("ft_strchr: %s\n", ft_strchr(s, 'l' - 516));
// 	ft_printf("strchr: %s\n", strchr(s, 'l' - 516));
// 	ft_printf("ft_strchr: %s\n", ft_strchr(s, 'b' - 516));
// 	ft_printf("strchr: %s\n", strchr(s, 'b' - 516));
// 	return (0);
// }