/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 04:43:58 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 15:44:36 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0' || needle == NULL)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	ft_printf("1\n");
// 	char *haystack = "Hello, World!";
// 	char *needle = "World";
// 	char *ret = ft_strnstr(haystack, needle, 13);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(haystack, needle, 13);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("2\n");
// 	ret = ft_strnstr(haystack, needle, 0);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(haystack, needle, 0);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("3\n");
// 	ret = ft_strnstr(haystack, needle, 1);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(haystack, needle, 1);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("4\n");
// 	ret = ft_strnstr("", needle, 5);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr("", needle, 5);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("5\n");
// 	ret = ft_strnstr(haystack, "", 5);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(haystack, "", 5);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("6\n");
// 	ret = ft_strnstr("", "", 5);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr("", "", 5);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("7\n");
// 	ret = ft_strnstr("", "", 0);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr("", "", 0);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("8\n");
// 	ret = ft_strnstr(haystack, "", 0);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(haystack, "", 0);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("9\n");
// 	ret = ft_strnstr("", needle, 0);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr("", needle, 0);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("10\n");
// 	ret = ft_strnstr(NULL, needle, 5);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(NULL, needle, 5);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("11\n");
// 	ret = ft_strnstr(haystack, NULL, 5);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(haystack, NULL, 5);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("12\n");
// 	ret = ft_strnstr(NULL, NULL, 5);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(NULL, NULL, 5);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("13\n");
// 	ret = ft_strnstr(NULL, NULL, 0);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(NULL, NULL, 0);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("14\n");
// 	ret = ft_strnstr(haystack, NULL, 0);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(haystack, NULL, 0);
// 	ft_printf("strnstr: %s\n", ret);

// 	ft_printf("15\n");
// 	ret = ft_strnstr(NULL, needle, 0);
// 	ft_printf("ft_strnstr: %s\n", ret);
// 	ret = strnstr(NULL, needle, 0);
// 	ft_printf("strnstr: %s\n", ret);

// 	return (0);
// }