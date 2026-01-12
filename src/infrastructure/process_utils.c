/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:25:49 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:25:50 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/process_interface.h"
#include "utils/libft_custom.h"
#include <stdlib.h>
#include <sys/wait.h>

bool	process_is_running(pid_t pid)
{
	int	status;

	if (pid <= 0)
		return (false);
	if (waitpid(pid, &status, WNOHANG) == 0)
		return (true);
	return (false);
}

char	*process_get_error_message(t_process_result result)
{
	if (result == PROCESS_ERROR_FORK)
		return (ft_strdup("Fork failed"));
	else if (result == PROCESS_ERROR_EXEC)
		return (ft_strdup("Exec failed"));
	else if (result == PROCESS_ERROR_WAIT)
		return (ft_strdup("Wait failed"));
	else if (result == PROCESS_ERROR_PIPE)
		return (ft_strdup("Pipe operation failed"));
	else if (result == PROCESS_ERROR_DUP)
		return (ft_strdup("File descriptor operation failed"));
	else if (result == PROCESS_ERROR_ACCESS)
		return (ft_strdup("Access denied"));
	return (ft_strdup("Unknown process error"));
}

void	destroy_process_service(t_process_service *service)
{
	if (service)
		free(service);
}
