/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:29:54 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/15 10:09:29 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_last_char(char *temp)
{
	int	i;

	i = 1;
	while (temp[i] != 0 && ft_strchr(" \"'$?/", temp[i]) == 0)
		i++;
	if (temp[i] != ' ' && temp[i] != 0)
		return (1);
	return (0);
}

char	*check_null_cmd(char *line, t_env **env)
{
	char	*temp;	
	char	*newline;

	newline = 0;
	temp = line;
	temp = ft_skip_whitespace(temp);
	if (*temp == '$')
	{
		if (check_last_char(temp) > 0)
			return (line);
		if (ft_get_env(&temp[1], env) == 0)
		{
			temp++;
			while (*temp != 0 && ft_strchr(" \"'$?/", *temp) == 0)
				temp++;
			newline = ft_strndup(temp, ft_strlen(temp));
			if (newline == 0)
				return (0);
			free(line);
			return (newline);
		}
	}
	return (line);
}

int	word_count(char *str)
{
	int		count;
	char	*temp;

	count = 0;
	if (str == 0)
		return (count);
	temp = str;
	while (*temp != 0)
	{
		if (*temp != ' ' && *temp != 0)
			count++;
		while (*temp != ' ' && *temp != 0)
			temp++;
		if (*temp != 0)
			temp++;
	}
	return (count);
}

char	*count_expand_cmd(char *cmd, int i, t_env **env)
{
	char	*str;

	str = 0;
	if (count_env_variables(cmd) > 0)
	{
		str = ft_strdup("");
		if (str == 0)
			return (0);
		cmd = expand_all_env(cmd, str, i, env);
	}
	if (cmd == 0)
	{
		free(str);
		return (0);
	}
	return (cmd);
}

void	change_cmd_status(t_env **env_t, int status)
{
	int	i;

	i = 0;
	if (status > 0)
		status = status / 256;
	while (i < TABLE_SIZE)
	{
		if (env_t[i] != (t_env *)(DELETED_NODE) && env_t[i] != NULL)
			env_t[i]->status = status;
		i++;
	}
}
