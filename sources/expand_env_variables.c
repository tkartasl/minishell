/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:46:47 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/22 10:44:15 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_env_variable(char *temp, int len, int *error, t_env **env)
{
	char	*expanded_var;
	char	*env_var;
	int		i;

	i = find_correct_index(env);
	if (*temp == '?')
	{
		expanded_var = ft_itoa(env[i]->status);
		if (expanded_var == 0)
		{
			*error = 1;
			return (0);
		}
		*error = 2;
		return (expanded_var);
	}
	env_var = ft_strndup(temp, len);
	if (env_var == 0)
	{
		*error = 1;
		return (0);
	}
	expanded_var = ft_get_env(env_var, env);
	free(env_var);
	return (expanded_var);
}

static char	*check_env_variable(char *str, int *error_flag, t_env **env)
{
	char	*temp;
	int		len;

	len = 0;
	temp = str;
	while (*temp != 0)
	{
		if (*temp == '$')
		{
			if (*temp == '$' && (*(temp + 1) == ' ' || *(temp + 1) == 0))
				return (temp);
			temp++;
			len++;
			while (temp[len] != 0 && ft_strchr(" ?'\"$/=", temp[len]) == 0)
				len++;
			if (len == 1 && *temp != '?')
				temp--;
			temp = expand_env_variable(temp, len, error_flag, env);
			if (temp == 0)
				return (0);
			return (temp);
		}
		temp++;
	}
	return (str);
}

char	*cpy_quote_to_quote(char *str, char *expanded_str, int *i)
{
	char	*temp;

	temp = 0;
	*i += 1;
	while (str[*i] != '\'' && str[*i] != 0)
		*i += 1;
	if (str[*i] == '\'')
		*i += 1;
	temp = ft_strndup(str, *i);
	if (temp == 0)
		return (0);
	expanded_str = ft_strjoin_free(expanded_str, temp);
	if (expanded_str == 0)
		return (0);
	free(temp);
	return (expanded_str);
}

char	*cpy_line(char *str, char *expanded_str, int *i, int *flag)
{
	char	*temp;

	(void)flag;
	temp = 0;
	while (str[*i] != 0 && str[*i] != '"' && str[*i] != '$')
		*i += 1;
	temp = ft_strndup(str, *i);
	if (temp == 0)
		return (0);
	expanded_str = ft_strjoin_free(expanded_str, temp);
	if (expanded_str == 0)
		return (0);
	free(temp);
	return (expanded_str);
}

char	*cpy_expanded(char *str, char *expanded_str, int *i, t_env **env)
{
	char	*temp;
	int		error_flag;

	error_flag = 0;
	temp = 0;
	temp = check_env_variable(str, &error_flag, env);
	if (error_flag == 1)
		return (0);
	if (temp != 0)
		expanded_str = ft_strjoin_free(expanded_str, temp);
	if (error_flag == 2)
		free(temp);
	if (expanded_str == 0)
		return (0);
	*i += 1;
	while (str[*i] != 0 && ft_strchr(" '\"$/=", str[*i]) == 0)
		*i += 1;
	return (expanded_str);
}
