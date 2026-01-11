/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usecase/env/env_manager.h"
#include "usecase/executor/executor.h"
#include "utils/libft_custom.h"
#include <stdlib.h>

char	*get_variable_value(const char *var_name, t_exec_context *ctx)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(ctx->last_exit_status));
	value = env_get(*ctx->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*extract_braced_var(const char *str, int *end_pos)
{
	int		end;
	char	*var_name;

	end = 2;
	while (str[end] && str[end] != '}')
		end++;
	if (!str[end])
		return (NULL);
	var_name = malloc(end - 2 + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str + 2, end - 2 + 1);
	*end_pos = end + 1;
	return (var_name);
}

static char	*extract_simple_var(const char *str, int *end_pos)
{
	int		end;
	char	*var_name;

	end = 1;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	*end_pos = end;
	if (end == 1)
		return (NULL);
	var_name = malloc(end - 1 + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str + 1, end - 1 + 1);
	return (var_name);
}

char	*extract_variable_name(const char *str, int *end_pos)
{
	if (str[1] == '?')
	{
		*end_pos = 2;
		return (ft_strdup("?"));
	}
	if (str[1] == '{')
		return (extract_braced_var(str, end_pos));
	return (extract_simple_var(str, end_pos));
}

char	*join_parts(char *before, char *value, char *after)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(before, value);
	result = ft_strjoin(temp, after);
	free(temp);
	return (result);
}

static int	find_dollar_pos(const char *str)
{
	int	pos;

	pos = 0;
	while (str[pos] && str[pos] != '$')
		pos++;
	return (pos);
}

char	*expand_single_variable(const char *str, t_exec_context *ctx)
{
	char	*var_name;
	char	*parts[3];
	char	*result;
	int		dollar_pos;
	int		var_end_pos;

	dollar_pos = find_dollar_pos(str);
	if (!str[dollar_pos])
		return (ft_strdup(str));
	var_name = extract_variable_name(str + dollar_pos, &var_end_pos);
	if (!var_name)
		return (ft_strdup(str));
	parts[0] = ft_substr(str, 0, dollar_pos);
	parts[1] = get_variable_value(var_name, ctx);
	parts[2] = ft_strdup(str + dollar_pos + var_end_pos);
	result = join_parts(parts[0], parts[1], parts[2]);
	free(var_name);
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	return (result);
}
