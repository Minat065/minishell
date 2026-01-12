/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:01:09 by mirokugo          #+#    #+#             */
/*   Updated: 2026/01/12 15:44:36 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
	return (c);
}

// int	main(void)
// {
// 	int i = 0;

// 	while (i < 128)
// 	{
// 		ft_printf("ft_toupper: %d  ", ft_toupper(i));
// 		ft_printf("   toupper: %d\n", toupper(i));
// 		ft_printf("\n");
// 		i++;
// 	}
// }
