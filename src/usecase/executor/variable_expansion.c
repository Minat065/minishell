/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:00:00 by tatsato           #+#    #+#             */
/*   Updated: 2025/06/18 00:00:00 by tatsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

char	*expand_single_variable(const char *str, t_exec_context *ctx);

char	*expand_variables(const char *str, t_exec_context *ctx)
{
	char	*result;
	char	*temp;
	int		has_dollar;

	if (!str || !ctx)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	has_dollar = 1;
	while (has_dollar)
	{
		temp = result;
		result = expand_single_variable(temp, ctx);
		has_dollar = (ft_strchr(result, '$') != NULL);
		if (ft_strcmp(temp, result) == 0)
			has_dollar = 0;
		free(temp);
		if (!result)
			return (NULL);
	}
	return (result);
}

static char	*expand_dquote_content(const char *str, t_exec_context *ctx)
{
	char	*content;
	char	*expanded;
	char	*result;

	content = ft_strdup(str + 1);
	if (!content)
		return (NULL);
	expanded = expand_variables(content, ctx);
	free(content);
	if (!expanded)
		return (NULL);
	result = ft_strjoin("\x02", expanded);
	free(expanded);
	return (result);
}

static void	expand_arg(t_cmd *cmd, int i, t_exec_context *ctx)
{
	char	*expanded;

	if (cmd->argv[i][0] == '\x01')
		return ;
	if (cmd->argv[i][0] == '\x02')
		expanded = expand_dquote_content(cmd->argv[i], ctx);
	else
		expanded = expand_variables(cmd->argv[i], ctx);
	if (expanded)
	{
		free(cmd->argv[i]);
		cmd->argv[i] = expanded;
	}
}

void	expand_command_variables(t_cmd *cmd, t_exec_context *ctx)
{
	int	i;

	if (!cmd || !cmd->argv || !ctx)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		expand_arg(cmd, i, ctx);
		i++;
	}
}
