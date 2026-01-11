/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by claude           ###   ########.fr       */
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
