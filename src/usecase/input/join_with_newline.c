/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_with_newline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 22:59:58 by mokabe            #+#    #+#             */
/*   Updated: 2025/10/29 23:14:23 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/libft_custom.h"
#include <stdlib.h>

char	*join_with_newline_and_strip_bslash(char *a, const char *b,
		int strip_bslash)
{
	size_t	la;
	size_t	lb;
	size_t	extra;
	char	*res;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	extra = 1;
	if (strip_bslash)
	{
		if (la > 0)
			la--;
		extra = 0;
	}
	res = malloc(la + extra + lb + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, a, la);
	if (extra)
		res[la++] = '\n';
	ft_memcpy(res + la, b, lb);
	res[la + lb] = '\0';
	return (res);
}
