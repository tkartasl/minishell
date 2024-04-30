/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:43:42 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/30 09:41:49 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_syntax(char **line)
{
	(*line)++;
	if (**line == ' ')
	{
		(*line) = ft_skip_whitespace((*line));
		if (**line == '<' || **line == '>' || **line == '|' || **line == '&')
			return (1);
	}
	if (**line == '&' || **line == '|')
		return (1);
	if (**line == '<' || **line == '>')
		line++;
	if (**line == '<' || **line == '>' || **line == '|' || **line == '&')
		return (1);
	return (0);
}

int	check_newline(char **cmd_line, t_env **env, int i)
{
	char	*line;

	line = cmd_line[i];
	while (*line != 0)
	{
		if (*line == '\n')
		{
			syntax_error(0, env, 'X');
			return (1);
		}
		line++;
	}
	if (*line == 0)
	{
		line--;
		while (*line == ' ')
			line--;
		if (*line == '<' || *line == '>')
		{
			ft_free_pointer_array(cmd_line);
			syntax_error(0, env, 'X');
			return (1);
		}
	}
	return (0);
}

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

static char	*check_env_cmd(char *line, char *temp, t_env **env, int *flag)
{
	char	*cmd;
	char	*newline;
	char	*exp_cmd;

	newline = 0;
	cmd = ft_strndup(&temp[1], get_len(&temp[1]));
	if (cmd == 0)
		return (0);
	exp_cmd = ft_get_env(cmd, env);
	free(cmd);
	if (exp_cmd == 0)
	{
		temp++;
		while (*temp != 0 && ft_strchr(" \"'$?/", *temp) == 0)
			temp++;
		if (*temp == 0)
			return (0);
		newline = ft_strndup(temp, ft_strlen(temp));
		if (newline == 0)
			return (0);
		free(line);
		*flag = 1;
		return (newline);
	}
	return (line);
}

char	*check_null_cmd(char **line, int i, t_env **env)
{
	char	*temp;	
	char	*newline;
	int		flag;

	flag = 0;
	newline = 0;
	temp = line[i];
	temp = ft_skip_whitespace(temp);
	if (*temp == '$')
	{
		if (check_last_char(temp) > 0)
			return (line[i]);
		newline = check_env_cmd(line[i], temp, env, &flag);
		if (newline == 0)
		{
			ft_free_pointer_array(line);
			return (0);
		}
	}
	if (flag == 1)
		return (newline);
	return (line[i]);
}
