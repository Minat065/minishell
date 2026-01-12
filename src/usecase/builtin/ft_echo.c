/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 22:50:01 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:26:03 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/output_interface.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

/**
 * @brief Prints the given strings to stdout, separated by spaces.
 * @param argv The array of strings to print.
 * @return 0 on success, 1 on failure (e.g., if writing to stdout fails).
 */
static int	print_echo(char **argv, t_output_service *out)
{
	while (*argv)
	{
		if (out->write_stdout(*argv) != OUTPUT_SUCCESS)
			return (EXIT_FAILURE);
		if (*(argv + 1))
			out->write_stdout(" ");
		argv++;
	}
	return (EXIT_SUCCESS);
}

static int	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * echo with option -n
 *
 * @brief Prints the given string to stdout.
 * If the string is NULL, it prints an empty line.
 * @param str The string to print.
 * @return 0 on success, 1 on failure (e.g., if writing to stdout fails).
 */
int	ft_echo(char **argv, t_output_service *out)
{
	int	newline;
	int	result;

	if (!out)
		return (EXIT_FAILURE);
	newline = 1;
	if (!argv || !*argv)
	{
		out->write_stdout("\n");
		return (EXIT_SUCCESS);
	}
	while (*argv && is_n_flag(*argv))
	{
		newline = 0;
		argv++;
	}
	result = print_echo(argv, out);
	if (result != 0)
		return (EXIT_FAILURE);
	if (newline)
	{
		if (out->write_stdout("\n") != OUTPUT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
