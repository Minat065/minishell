/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:29:20 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:29:22 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/libft_custom.h"

int	validate_assignment_first_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	validate_assignment(char *str)
{
	if (*str == '+')
	{
		if (*(str + 1) == '=')
			return (1);
	}
	return (ft_isalnum(*str) || *str == '_');
}
