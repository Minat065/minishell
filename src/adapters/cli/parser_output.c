/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/10/14 22:17:26 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adapters/cli/parser_output.h"
#include "adapters/parser/parser_interface.h"
#include "domain/command.h"
#include "utils/libft_custom.h"
#include <stdio.h>
#include <unistd.h>

static void	count_pipelines_and_commands(t_parse_result *result, int *counts)
{
	t_pipeline	*current_pipeline;
	t_cmd		*current_cmd;

	counts[0] = 0;
	counts[1] = 0;
	current_pipeline = result->ast;
	while (current_pipeline)
	{
		counts[0]++;
		current_cmd = current_pipeline->cmds;
		while (current_cmd)
		{
			counts[1]++;
			current_cmd = current_cmd->next;
		}
		current_pipeline = current_pipeline->next;
	}
}

static void	print_parser_error(t_parse_result *result)
{
	if (result && result->error_msg)
		ft_putendl_fd(result->error_msg, STDERR_FILENO);
}

static void	print_ast_statistics(int *counts)
{
	(void)counts;
}

void	print_parse_result(t_parse_result *result)
{
	int	counts[2];

	if (!result)
		return ;
	if (result->error_msg)
	{
		print_parser_error(result);
		return ;
	}
	if (!result->ast)
		return ;
	count_pipelines_and_commands(result, counts);
	print_ast_statistics(counts);
}
