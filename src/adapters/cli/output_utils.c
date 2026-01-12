/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokabe <mokabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2026/01/12 11:20:23 by mokabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adapters/cli/output_utils.h"
#include "adapters/parser/parser_interface.h"
#include "domain/command.h"
#include "domain/token.h"
#include "usecase/executor/executor.h"
#include <stdio.h>

void	print_indent(int depth)
{
	(void)depth;
}

void	print_pipeline_cmds(t_pipeline *ast, int depth)
{
	(void)ast;
	(void)depth;
}

void	print_ast_debug(t_pipeline *ast, int depth)
{
	(void)ast;
	(void)depth;
}

void	print_ast(t_pipeline *ast)
{
	print_ast_debug(ast, 1);
}

void	print_execution_summary(int status, t_exec_context *ctx)
{
	(void)status;
	(void)ctx;
}
