/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:50:27 by tatsato           #+#    #+#             */
/*   Updated: 2025/05/31 23:43:14 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/env/env_manager.h"
#include <stdlib.h>

/*
 * Removes environment variables from the linked list.
 */
int	ft_unset(char **argv, t_env_var **envp)
{
	char	*key;

	if (!argv || !*argv)
		return (EXIT_SUCCESS);
	while (*argv)
	{
		key = *argv++;
		if (key && *key)
			env_remove(envp, key);
	}
	return (EXIT_SUCCESS);
}
