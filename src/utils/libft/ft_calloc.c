/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:57:49 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:30:23 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;
	size_t	bytes;

	bytes = count * size;
	if (count != 0)
	{
		if (bytes / count != size)
			return (NULL);
	}
	mem = (char *)malloc(bytes);
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < bytes)
		mem[i++] = 0;
	return ((void *)mem);
}
