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

#include "usecase/exit/exit.h"
#include "utils/libft_custom.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static int	count_arg(char **argv)
{
	int	count;

	count = 0;
	while (argv && *argv)
	{
		count++;
		argv++;
	}
	return (count);
}

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

void	ft_exit(char **argv, t_token_stream *stream, t_env_var *env)
{
	long long	exit_code;
	int			argc;

	write(STDERR_FILENO, "exit\n", 5);
	if (!argv || !*argv)
		exit_minishell(0, stream, env);
	argc = count_arg(argv);
	if (argc > 1)
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 31);
		exit_minishell(1, stream, env);
	}
	if (can_convert_str_to_longlong(*argv) == 0)
	{
		write(STDERR_FILENO, "minishell: exit: numeric argument required\n",
			38);
		exit_minishell(255, stream, env);
	}
	exit_code = ft_atoll(*argv) % 256;
	if (exit_code < 0)
		exit_code += 256;
	exit_minishell(exit_code, stream, env);
}
