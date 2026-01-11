/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:57:29 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/16 08:38:12 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/output_interface.h"
#include "usecase/env/env_manager.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

static char	*build_env_line(t_env_var *var)
{
	char	*output;
	char	*temp;

	output = ft_strjoin(var->key, "=");
	if (!output)
		return (NULL);
	if (var->value)
	{
		temp = ft_strjoin(output, var->value);
		free(output);
		output = temp;
	}
	return (output);
}

int	ft_env(t_env_var *envp, t_output_service *out)
{
	t_env_var	*current;
	char		*output;

	if (!envp || !out)
		return (EXIT_FAILURE);
	current = envp;
	while (current)
	{
		output = build_env_line(current);
		if (!output)
			return (EXIT_FAILURE);
		if (out->write_stdout_newline(output) != OUTPUT_SUCCESS)
		{
			free(output);
			return (EXIT_FAILURE);
		}
		free(output);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
