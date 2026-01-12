/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:59:34 by mirokugo          #+#    #+#             */
/*   Updated: 2024/06/23 14:54:46 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd, int *count_char)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	write(fd, s, len);
	if (count_char)
		*count_char += len;
	if (count_char)
		return (*count_char);
	return (len);
}
