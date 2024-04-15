/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:43:42 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/15 14:41:09 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_syntax(char *line)
{
	line++;
	if (*line == '&' || *line == '|')
		return (1);
	if (*line == '<' || *line == '>')
		line++;
	if (*line == '<' || *line == '>' || *line == '|' || *line == '&')
		return (1);
	return (0);
}

int	check_newline(char *line, t_env **env)
{
	while (*line != 0)
	{
		if (*line == '\n')
		{
			syntax_error(0, env, 'X');
			return (1);
		}
		line++;
	}
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
	if (exp_cmd == 0)
	{
		temp++;
		while (*temp != 0 && ft_strchr(" \"'$?/", *temp) == 0)
			temp++;
		newline = ft_strndup(temp, ft_strlen(temp));
		if (newline == 0)
			return (0);
		free(line);
		*flag = 1;
		return (newline);
	}
	return (line);
}

char	*check_null_cmd(char *line, t_env **env)
{
	char	*temp;	
	char	*newline;
	int		flag;

	flag = 0;
	newline = 0;
	temp = line;
	temp = ft_skip_whitespace(temp);
	if (*temp == '$')
	{
		if (check_last_char(temp) > 0)
			return (line);
		newline = check_env_cmd(line, temp, env, &flag);
		if (newline == 0)
			return (0);
	}
	if (flag == 1)
		return (newline);
	return (line);
}

