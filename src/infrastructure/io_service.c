/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_service.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:24:55 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:24:56 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/io_interface.h"
#include "utils/libft_custom.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

static t_io_result	impl_change_directory(const char *path)
{
	if (!path)
		return (IO_ERROR_ACCESS);
	if (chdir(path) == -1)
	{
		if (errno == EACCES)
			return (IO_ERROR_PERMISSION);
		else if (errno == ENOENT)
			return (IO_ERROR_NOT_FOUND);
		else
			return (IO_ERROR_SYSTEM);
	}
	return (IO_SUCCESS);
}

static char	*impl_get_current_directory(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	return (cwd);
}

static bool	impl_file_exists(const char *path)
{
	struct stat	st;

	if (!path)
		return (false);
	return (stat(path, &st) == 0);
}

bool				impl_is_directory(const char *path);
char				*impl_get_error_message(t_io_result result);

t_io_service	*create_io_service(void)
{
	t_io_service	*service;

	service = malloc(sizeof(t_io_service));
	if (!service)
		return (NULL);
	service->change_directory = impl_change_directory;
	service->get_current_directory = impl_get_current_directory;
	service->file_exists = impl_file_exists;
	service->is_directory = impl_is_directory;
	service->get_error_message = impl_get_error_message;
	return (service);
}
