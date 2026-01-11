/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:03:51 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/16 08:37:50 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/io_interface.h"
#include "interfaces/output_interface.h"
#include "usecase/env/env_manager.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

/**
 * get_path - Get the path to change to.
 * @arg_count: Number of arguments passed to the command.
 * @argv: Array of arguments, where the first argument is the path.
 * @envp: Pointer to the head of the linked list of environment variables.
 *
 * If no arguments are provided,
 * it retrieves the HOME directory from the environment.
 * If "-" is provided, it retrieves the OLDPWD directory.
 * If an argument is provided, it uses that as the path.
 *
 * Return: The path to change to,
 * or NULL if HOME/OLDPWD is not set and needed.
 */
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

/*
 * Changes current directory to the specified path.
 * If no path is specified, changes to HOME directory.
 * Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	ft_cd(char **argv, t_env_var **envp, t_io_service *io,
		t_output_service *out)
{
	char		*path;
	char		*cwd;
	char		*new_cwd;
	t_io_result	result;
	int			print_path;

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
	result = io->change_directory(path);
	if (result != IO_SUCCESS)
		return (handle_cd_error(path, cwd, io, out));
	env_add(envp, "OLDPWD", cwd, "=");
	new_cwd = io->get_current_directory();
	if (new_cwd)
	{
		env_add(envp, "PWD", new_cwd, "=");
		if (print_path)
			out->write_stdout_newline(new_cwd);
		free(new_cwd);
	}
	free(cwd);
	return (EXIT_SUCCESS);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_var	*env = env_create_from_envp(envp);
// 	int			result;

// 	result = ft_cd(argv + 1, &env);
// 	env_free(env);
// 	return (result);
// }
