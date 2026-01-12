/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:26:14 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 13:57:58 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static int	can_convert_str_to_positive_longlong(const char *str)
{
	long long	result;
	int			digit;
	int			has_digit;

	result = 0;
	has_digit = 0;
	while (ft_isdigit(*str))
	{
		has_digit = 1;
		digit = *str - '0';
		if (result > (LLONG_MAX - digit) / 10)
			return (0);
		result = result * 10 + digit;
		str++;
	}
	if (!has_digit || *str != '\0')
		return (0);
	return (1);
}

static int	can_convert_str_to_negative_longlong(const char *str)
{
	long long	result;
	int			digit;
	int			has_digit;

	result = 0;
	has_digit = 0;
	while (ft_isdigit(*str))
	{
		has_digit = 1;
		digit = *str - '0';
		if (result < (LLONG_MIN + digit) / 10)
			return (0);
		result = result * 10 - digit;
		str++;
	}
	if (!has_digit || *str != '\0')
		return (0);
	return (1);
}

static int	can_convert_str_to_longlong(const char *str)
{
	if (*str == '-')
	{
		str++;
		return (can_convert_str_to_negative_longlong(str));
	}
	else if (*str == '+')
	{
		str++;
		return (can_convert_str_to_positive_longlong(str));
	}
	else
		return (can_convert_str_to_positive_longlong(str));
}

int	ft_exit(char **argv, t_exec_context *ctx)
{
	long long	exit_code;

	write(STDERR_FILENO, "exit\n", 5);
	if (!argv || !*argv)
		return (ctx->should_exit = 1, ctx->exit_code = 0, 0);
	if (argv[1])
		return (write(STDERR_FILENO, "minishell: exit: too many arguments\n",
				37), 1);
	if (!can_convert_str_to_longlong(argv[0]))
		return (write(STDERR_FILENO,
				"minishell: exit: numeric argument required\n", 38),
			ctx->should_exit = 1, ctx->exit_code = 255, 255);
	exit_code = ft_atoll(argv[0]) % 256;
	if (exit_code < 0)
		exit_code += 256;
	ctx->should_exit = 1;
	ctx->exit_code = (int)exit_code;
	return ((int)exit_code);
}
