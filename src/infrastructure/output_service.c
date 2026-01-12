/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_service.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:25:10 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:25:12 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/output_interface.h"
#include "utils/libft_custom.h"
#include <stdlib.h>
#include <unistd.h>

/* No global variables - using dependency injection */

static t_output_result	impl_write_stdout(const char *message)
{
	if (!message)
		return (OUTPUT_ERROR_WRITE);
	if (write(STDOUT_FILENO, message, ft_strlen(message)) == -1)
		return (OUTPUT_ERROR_SYSTEM);
	return (OUTPUT_SUCCESS);
}

static t_output_result	impl_write_stderr(const char *message)
{
	if (!message)
		return (OUTPUT_ERROR_WRITE);
	if (write(STDERR_FILENO, message, ft_strlen(message)) == -1)
		return (OUTPUT_ERROR_SYSTEM);
	return (OUTPUT_SUCCESS);
}

static t_output_result	impl_write_stdout_newline(const char *message)
{
	t_output_result	result;

	result = impl_write_stdout(message);
	if (result != OUTPUT_SUCCESS)
		return (result);
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		return (OUTPUT_ERROR_SYSTEM);
	return (OUTPUT_SUCCESS);
}

static t_output_result	impl_write_stderr_newline(const char *message)
{
	t_output_result	result;

	result = impl_write_stderr(message);
	if (result != OUTPUT_SUCCESS)
		return (result);
	if (write(STDERR_FILENO, "\n", 1) == -1)
		return (OUTPUT_ERROR_SYSTEM);
	return (OUTPUT_SUCCESS);
}

t_output_result			impl_write_fd(int fd, const char *message);

t_output_service	*create_output_service(void)
{
	t_output_service	*service;

	service = malloc(sizeof(t_output_service));
	if (!service)
		return (NULL);
	service->write_stdout = impl_write_stdout;
	service->write_stderr = impl_write_stderr;
	service->write_stdout_newline = impl_write_stdout_newline;
	service->write_stderr_newline = impl_write_stderr_newline;
	service->write_fd = impl_write_fd;
	return (service);
}
