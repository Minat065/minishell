/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:26:38 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/env/env_manager.h"
#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include <stdlib.h>
#include <unistd.h>

static char	*check_absolute_path(const char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

static char	*search_in_paths(const char *cmd, char **paths)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp)
		{
			full_path = ft_strjoin(temp, cmd);
			free(temp);
			if (full_path && access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
		}
		i++;
	}
	return (NULL);
}

/* Find command path using PATH environment variable */
char	*find_command_path(const char *cmd, t_env_var *env)
{
	char	*path_env;
	char	**paths;
	char	*result;

	result = check_absolute_path(cmd);
	if (result)
		return (result);
	path_env = env_get(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(cmd, paths);
	free_envp(paths);
	return (result);
}
