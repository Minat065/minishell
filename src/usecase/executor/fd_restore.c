/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_restore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:27:01 by mokabe            #+#    #+#             */
/*   Updated: 2026/01/12 11:27:02 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/process_interface.h"
#include <unistd.h>

void	restore_redirections_with_service(int saved_stdin, int saved_stdout,
		t_process_service *proc_service)
{
	if (saved_stdin != -1)
	{
		proc_service->dup_fd(saved_stdin, STDIN_FILENO);
		proc_service->close_fd(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		proc_service->dup_fd(saved_stdout, STDOUT_FILENO);
		proc_service->close_fd(saved_stdout);
	}
}

void	restore_redirections(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
