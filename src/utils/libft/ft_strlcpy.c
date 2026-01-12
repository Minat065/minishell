/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 03:38:52 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 15:44:36 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize == 1)
		dst[0] = '\0';
	if (src[i] == '\0' && i < dstsize)
		dst[i] = '\0';
	if (i > 0 && i + 1 == dstsize)
		dst[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i);
}

// int	main(void)
// {
// 	char s[10] = "123456789";
// 	char s2[10] = "123456789";
// 	ft_printf("ft_strlcpy: %d, %s\n", ft_strlcpy(s, "abc", 5), s);
// 	ft_printf("strlcpy: %lu, %s\n", strlcpy(s2, "abc", 5), s2);

// 	char s3[10] = "123456789";
// 	char s4[10] = "123456789";
// 	ft_printf("ft_strlcpy: %d, %s\n", ft_strlcpy(s3, "abc", 0), s3);
// 	ft_printf("strlcpy: %lu, %s\n", strlcpy(s4, "abc", 0), s4);

// 	char s5[10] = "123456789";
// 	char s6[10] = "123456789";
// 	ft_printf("ft_strlcpy: %d, %s\n", ft_strlcpy(s5, "abc", 10), s5);
// 	ft_printf("strlcpy: %lu, %s\n", strlcpy(s6, "abc", 10), s6);

// 	char s7[10] = "123456789";
// 	char s8[10] = "123456789";
// 	ft_printf("ft_strlcpy: %d, %s\n", ft_strlcpy(s7, "abc", 3), s7);
// 	ft_printf("strlcpy: %lu, %s\n", strlcpy(s8, "abc", 3), s8);

// 	char s9[10] = "123456789";
// 	char s10[10] = "123456789";
// 	ft_printf("ft_strlcpy: %d, %s\n", ft_strlcpy(s9, "abc", 2), s9);
// 	ft_printf("strlcpy: %lu, %s\n", strlcpy(s10, "abc", 2), s10);

// 	char s11[10] = "123456789";
// 	char s12[10] = "123456789";
// 	ft_printf("ft_strlcpy: %d, %s\n", ft_strlcpy(s11, "abc", 1), s11);
// 	ft_printf("strlcpy: %lu, %s\n", strlcpy(s12, "abc", 1), s12);
// 	return (0);
// }