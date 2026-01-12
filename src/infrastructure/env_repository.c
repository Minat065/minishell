/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_repository.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:24:47 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:24:49 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/env_repository.h"
#include "usecase/env/env_manager.h"
#include <stdlib.h>

/* Simplified implementation
	- environmental variables are managed at exec context level */

t_env_repository	*create_env_repository(void)
{
	t_env_repository	*repo;

	repo = malloc(sizeof(t_env_repository));
	if (!repo)
		return (NULL);
	repo->add_var = NULL;
	repo->add_assign = NULL;
	repo->remove_var = NULL;
	repo->get_var = NULL;
	repo->get_all_vars = NULL;
	repo->init_envp = NULL;
	repo->cleanup = NULL;
	return (repo);
}

void	destroy_env_repository(t_env_repository *repository)
{
	if (repository)
		free(repository);
}
