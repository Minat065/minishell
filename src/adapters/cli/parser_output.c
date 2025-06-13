/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/13 23:40:29 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "adapters/cli/parser_output.h"
#include "usecase/parser/parser_interface.h"
#include "domain/command.h"

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

void	print_parse_result(t_parse_result *result)
{
	int	counts[2];

	printf("=== Parser Results ===\n");
	if (!result)
	{
		printf("❌ Parser failed: result is NULL\n");
		return ;
	}
	if (result->error_msg)
	{
		printf("❌ Parser error: %s", result->error_msg);
		if (result->error_line > 0 || result->error_column > 0)
			printf(" (line %d, column %d)", result->error_line,
				result->error_column);
		printf("\n");
		return ;
	}
	if (!result->ast)
	{
		printf("❌ Parser failed: AST is NULL\n");
		return ;
	}
	printf("✅ Parser successful! AST created\n");
	count_pipelines_and_commands(result, counts);
	printf("📊 AST structure:\n");
	printf("   - Pipelines: %d\n", counts[0]);
	printf("   - Total commands: %d\n", counts[1]);
	if (counts[1] > counts[0])
		printf("   - Contains pipes: YES\n");
	printf("\n");
}

