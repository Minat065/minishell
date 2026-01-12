/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:25:02 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:25:04 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/io_interface.h"
#include "utils/libft_custom.h"
#include <stdlib.h>
#include <sys/stat.h>

bool	impl_is_directory(const char *path)
{
	struct stat	st;

	if (!path || stat(path, &st) == -1)
		return (false);
	return (S_ISDIR(st.st_mode));
}

char	*impl_get_error_message(t_io_result result)
{
	if (result == IO_ERROR_ACCESS)
		return (ft_strdup("Access denied"));
	else if (result == IO_ERROR_NOT_FOUND)
		return (ft_strdup("No such file or directory"));
	else if (result == IO_ERROR_PERMISSION)
		return (ft_strdup("Permission denied"));
	else if (result == IO_ERROR_SYSTEM)
		return (ft_strdup("System error"));
	return (ft_strdup("Unknown error"));
}

void	destroy_io_service(t_io_service *service)
{
	if (service)
		free(service);
}
