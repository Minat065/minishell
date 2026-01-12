/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:26:14 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:57:41 by mokabe           ###   ########.fr       */
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

static int	normalize_exit_code(long long code)
{
	int	result;

	result = (int)(code % 256);
	if (result < 0)
		result += 256;
	return (result);
}

int	ft_exit(char **argv, t_exec_context *ctx)
{
	long long	exit_code;

	write(STDERR_FILENO, "exit\n", 5);
	if (!argv || !*argv)
	{
		ctx->should_exit = 1;
		ctx->exit_code = 0;
		return (0);
	}
	if (argv[0] && argv[1])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	if (can_convert_str_to_longlong(*argv) == 0)
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, *argv, ft_strlen(*argv));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		ctx->should_exit = 1;
		ctx->exit_code = 2;
		return (2);
	}
	exit_code = ft_atoll(*argv);
	ctx->should_exit = 1;
	ctx->exit_code = normalize_exit_code(exit_code);
	return (ctx->exit_code);
}
