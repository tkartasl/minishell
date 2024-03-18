/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:46:38 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/18 14:13:12 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_variable(char *temp, int len_var)
{
	char	*expanded_var;
	char    *env_var;

	env_var = ft_strndup(temp, len_var);
	if (env_var == 0)
		return (0);
	expanded_var = getenv(env_var);
	free(env_var);
	return (expanded_var);
}

char	*check_env_variable(char *str)
{
	char	*temp;
	int		len_var;

	len_var = 0;
	temp = str;
	while (*temp != 0)
	{
		if (*temp == '$')
		{
			temp++;
			len_var++;
			while (temp[len_var] != 0 && temp[len_var] != ' ' && temp[len_var]
				!= '$' && temp[len_var] != '\'' && temp[len_var] != '"')
				len_var++;
			if (len_var == 1)
				temp--;
			temp = expand_env_variable(temp, len_var);
			if (temp == 0)
				return (0);
			return (temp);
		}
		temp++;
	}
	return (str);
}

char	*skip_single_quotes(char *str, char quote)
{
	char	*temp;

	str++;
	temp = str;
	while (*str != 0 && *str != quote)
		str++;
	if (*str == 0)
		return (temp);
	return (str);
}

int	count_env_variables(char *str)
{
	char	*temp;
	int		env_count;

	temp = str;
	env_count = 0;
	while (*temp != 0)
	{
		if (*temp == '\'')
			temp = skip_single_quotes(temp, *temp);
		if (*temp == '$')
			env_count++;
		temp++;
	}
	return (env_count);
}

char	*lol(char *old_str)
{
	char	*temp;
	int		i;
	int		flag;
	char	*expanded_str;
	char	*str;

	str = old_str;
	expanded_str = ft_strdup("");
	if (expanded_str == 0)
		ft_printf("error");
	flag = 0;
	i = 0;
	temp = 0;
	while (*str != 0)
	{
		if (*str == '"')
			flag++;
		if (*str == '\'' && flag % 2 == 0)
		{
			str++;
			while (str[i] != '\'' && str[i] != 0)
				i++;
			temp = ft_strndup(str, i);
			if (temp == 0)
				ft_printf("error");
			expanded_str = ft_strjoin_free(expanded_str, temp);
			if (expanded_str == 0)
				ft_printf("error");
			free(temp);
			str = str + i;
			i = 0;
		}
		else if (*str == '$')
		{
			temp = check_env_variable(str);
			if (temp != 0)
				expanded_str = ft_strjoin_free(expanded_str, temp);
			if (expanded_str == 0)
				ft_printf("error");
			while (str[i] != ' ' && str[i] != '\'' && str[i] != '"' && str[i] != 0)
				i++;
			str = str + i;
			i = 0;	
		}
		else
		{
			while (str[i] != 0 && str[i] != '"' && str[i] != '$')
				i++;
			temp = ft_strndup(str, i);
			if (temp == 0)
				ft_printf("error");
			expanded_str = ft_strjoin_free(expanded_str, temp);
			if (expanded_str == 0)
				ft_printf("error");
			free(temp);
			str = str + i;
			i = 0;
			if (*str == '"')
			{
				str++;
				flag++;
			}
		}
	}
	free(old_str);
	return (expanded_str);
}
