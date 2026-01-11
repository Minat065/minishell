/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/process_interface.h"
#include "utils/libft_custom.h"
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
