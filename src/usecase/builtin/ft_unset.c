/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:50:27 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:26:23 by mokabe           ###   ########.fr       */
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
