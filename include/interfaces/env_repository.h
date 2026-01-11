/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_repository.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_REPOSITORY_H
# define ENV_REPOSITORY_H

# include "domain/assignment.h"
# include "domain/env_variable.h"

/* Environment repository operation results */
typedef enum e_env_result
{
	ENV_SUCCESS,
	ENV_ERROR_NOT_FOUND,
	ENV_ERROR_INVALID_KEY,
	ENV_ERROR_MEMORY
}					t_env_result;

typedef struct s_env_repository
{
	t_env_result	(*add_var)(const char *k, const char *v, const char *o);
	t_env_result	(*add_assign)(t_assignment *a);
	t_env_result	(*remove_var)(const char *key);
	char			*(*get_var)(const char *key);
	t_env_var		*(*get_all_vars)(void);
	t_env_result	(*init_envp)(char **envp);
	void			(*cleanup)(void);
}					t_env_repository;

/* Repository factory functions */
t_env_repository	*create_env_repository(void);
void				destroy_env_repository(t_env_repository *repository);

#endif