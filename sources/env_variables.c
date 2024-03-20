/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:46:38 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/20 12:43:46 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_env_variable(char *temp, int len_var, int *error_flag)
{
	char	*expanded_var;
	char    *env_var;

	env_var = ft_strndup(temp, len_var);
	if (env_var == 0)
	{
		*error_flag = 1;
		return (0);
	}
	expanded_var = getenv(env_var);
	free(env_var);
	return (expanded_var);
}

char	*check_env_variable(char *str, int *error_flag)
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
			temp = expand_env_variable(temp, len_var, error_flag);
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
	if (*(str + *i) == '"')
	{
		*i += 1;
		*flag += 1;;
	}
	return (expanded_str);
}

char	*cpy_expanded(char *str, char *expanded_str, int *i)
{
	char	*temp;
	int		error_flag;

	error_flag = 0;
	temp = 0;
	temp = check_env_variable(str, &error_flag);
	if (error_flag == 1)
		return (0);
	if (temp != 0)
		expanded_str = ft_strjoin_free(expanded_str, temp);
	if (expanded_str == 0)
		return (0);
	while (str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"' && str[*i] != 0)
		*i += 1;
	return (expanded_str);
}

char	*lol(char *old_str)
{
	int		i;
	int		flag;
	char	*expanded_str;
	char	*str;

	str = old_str;
	expanded_str = ft_strdup("");
	if (expanded_str == 0)
		ft_printf("error");
	flag = 0;
	while (*str != 0)
	{
		i = 0;
		ft_printf("%s\n", str);
		if (*str == '"')
		{
			flag++;
			str++;
		}
		if (*str == '\'' && flag % 2 == 0)
			expanded_str = cpy_quote_to_quote(str, expanded_str, &i);
		else if (*str == '$')
			expanded_str = cpy_expanded(str, expanded_str, &i);
		else
			expanded_str = cpy_line(str, expanded_str, &i, &flag);
		if (expanded_str == 0)
			return (0);
		str = str + i;
	}
	free(old_str);
	return (expanded_str);
}

int main()
{
	char	*s;

	s = ft_strdup("echo$USER'\"$MAIL$MAIL\"'");

	s = lol(s);
	ft_printf("%s\n", s);
	return (0);
}

/*void	check_cmd_env(char *cmd)
{
	char	*new_cmd;
	int		i;

	i = 0;
	new_cmd = 0;
	if (*cmd == '$')
		new_cmd = check_env_variable(cmd);
	while (new_cmd[i] != 0 && new_cmd[i] != ' ')
		i++;
	if (new_cmd[i] == ' ')
		something;
}*/