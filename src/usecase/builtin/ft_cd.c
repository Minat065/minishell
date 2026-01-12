/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:03:51 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:26:01 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/io_interface.h"
#include "interfaces/output_interface.h"
#include "usecase/env/env_manager.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

static char	*get_path(char **argv, t_env_var **envp, int *print_path)
{
	char	*path;

	*print_path = 0;
	if (!argv || !*argv)
	{
		path = env_get(*envp, "HOME");
		if (!path)
			return (NULL);
	}
	else if (ft_strcmp(*argv, "-") == 0)
	{
		path = env_get(*envp, "OLDPWD");
		if (!path)
			return (NULL);
		*print_path = 1;
	}
	else
		path = *argv;
	return (path);
}

static int	handle_cd_error(char *path, char *cwd, t_io_service *io,
		t_output_service *out)
{
	char	*err_msg;

	err_msg = ft_strjoin("minishell: cd: ", path);
	if (err_msg)
	{
		out->write_stderr(err_msg);
		out->write_stderr(": ");
		free(err_msg);
	}
	err_msg = io->get_error_message(IO_ERROR_NOT_FOUND);
	if (err_msg)
	{
		out->write_stderr_newline(err_msg);
		free(err_msg);
	}
	free(cwd);
	return (EXIT_FAILURE);
}

static void	set_new_pwd(t_env_var **envp, t_io_service *io, int print,
		t_output_service *out)
{
	char	*new_cwd;

	new_cwd = io->get_current_directory();
	if (new_cwd)
	{
		env_add(envp, "PWD", new_cwd, "=");
		if (print)
			out->write_stdout_newline(new_cwd);
		free(new_cwd);
	}
}

int	ft_cd(char **argv, t_env_var **envp, t_io_service *io,
		t_output_service *out)
{
	char	*path;
	char	*cwd;
	int		print_path;

	if (!io || !out)
		return (EXIT_FAILURE);
	cwd = io->get_current_directory();
	if (!cwd)
		return (EXIT_FAILURE);
	path = get_path(argv, envp, &print_path);
	if (!path)
	{
		out->write_stderr("minishell: cd: HOME not set\n");
		free(cwd);
		return (EXIT_FAILURE);
	}
	if (io->change_directory(path) != IO_SUCCESS)
		return (handle_cd_error(path, cwd, io, out));
	env_add(envp, "OLDPWD", cwd, "=");
	set_new_pwd(envp, io, print_path, out);
	free(cwd);
	return (EXIT_SUCCESS);
}
