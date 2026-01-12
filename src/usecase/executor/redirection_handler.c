/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 15:49:43 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/token.h"
#include "usecase/executor/executor.h"
#include "libft.h"
#include <unistd.h>

static int	process_redirection_with_service(t_cmd_redirect *current,
		t_process_service *proc_service)
{
	if (current->type == REDIRECT_INPUT)
		return (handle_input_redirect_with_service(current->file,
				proc_service));
	if (current->type == REDIRECT_OUTPUT)
		return (handle_output_redirect_with_service(current->file,
				proc_service));
	if (current->type == REDIRECT_APPEND)
		return (handle_append_redirect_with_service(current->file,
				proc_service));
	if (current->type == REDIRECT_HEREDOC)
	{
		if (current->heredoc_content)
			return (handle_heredoc_with_content(current->heredoc_content));
		return (handle_heredoc_redirect_with_service(current->file,
				proc_service));
	}
	ft_printf("minishell: unsupported redirection type\n");
	return (-1);
}

static int	process_redirection(t_cmd_redirect *current)
{
	if (current->type == REDIRECT_INPUT)
		return (handle_input_redirect(current->file));
	if (current->type == REDIRECT_OUTPUT)
		return (handle_output_redirect(current->file));
	if (current->type == REDIRECT_APPEND)
		return (handle_append_redirect(current->file));
	if (current->type == REDIRECT_HEREDOC)
	{
		if (current->heredoc_content)
			return (handle_heredoc_with_content(current->heredoc_content));
		return (handle_heredoc_redirect(current->file));
	}
	ft_printf("minishell: unsupported redirection type\n");
	return (-1);
}

int	setup_redirections_with_service(t_cmd_redirect *redirects,
		t_process_service *proc_service)
{
	t_cmd_redirect	*current;

	current = redirects;
	while (current)
	{
		if (process_redirection_with_service(current, proc_service) != 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	setup_redirections(t_cmd_redirect *redirects)
{
	t_cmd_redirect	*current;

	current = redirects;
	while (current)
	{
		if (process_redirection(current) != 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
