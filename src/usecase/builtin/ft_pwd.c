/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:27:44 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:26:20 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/io_interface.h"
#include "interfaces/output_interface.h"
#include <stdlib.h>

int	ft_pwd(t_io_service *io, t_output_service *out)
{
	char	*cwd;

	if (!io || !out)
		return (EXIT_FAILURE);
	cwd = io->get_current_directory();
	if (!cwd)
		return (EXIT_FAILURE);
	if (out->write_stdout_newline(cwd) != OUTPUT_SUCCESS)
	{
		free(cwd);
		return (EXIT_FAILURE);
	}
	free(cwd);
	return (EXIT_SUCCESS);
}
