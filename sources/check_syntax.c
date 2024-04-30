/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:52:38 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/30 09:18:38 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_empty_line(char **lines, int pipe_count, int i, t_env **env)
{
	char	*temp;

	temp = lines[i];
	temp = ft_skip_whitespace(temp);
	if (*temp == 0 && pipe_count == 1)
	{
		if (lines != 0)
			ft_free_pointer_array(lines);
		return (1);
	}
	if (*temp == '&')
	{
		syntax_error(lines, env, *temp);
		return (1);
	}
	if (*temp == 0 && i < pipe_count)
	{
		syntax_error(lines, env, '|');
		return (1);
	}
	return (0);
}

static int	check_after_redir(char **cmd_lines, int i, t_env **env)
{
	char	*temp;

	temp = cmd_lines[i];
	while (*temp)
	{
		if (*temp == '\'' || *temp == '\"')
			temp = skip_quotes(temp, *temp);
		if ((*temp == '<' && *(temp + 1) == '>')
			|| (*temp == '>' && *(temp + 1) == '<'))
		{
			syntax_error(cmd_lines, env, 'X');
			return (1);
		}
		if (*temp == '<' || *temp == '>')
		{
			if (check_redir_syntax(&temp) == 1)
			{
				syntax_error(cmd_lines, env, *temp);
				return (1);
			}
		}
		temp++;
	}
	return (0);
}

static int	check_unclosed_quotes(char **line, t_env **env, int i)
{
	char	*cmd;
	char	quote;

	cmd = line[i];
	while (*cmd != 0)
	{
		if (*cmd == '"' || *cmd == '\'')
		{
			quote = *cmd;
			cmd++;
			while (*cmd != 0 && *cmd != quote)
				cmd++;
		}
		if (*cmd == 0)
		{
			ft_free_pointer_array(line);
			change_cmd_status(env, 256);
			ft_putstr_fd("minishell: unclosed quotes\n", 2);
			return (-1);
		}
		cmd++;
	}
	return (0);
}

int	check_syntax(char **cmd_lines, int pipe_count, t_env **env)
{
	int	i;

	i = -1;
	while (cmd_lines[++i])
	{
		if (check_empty_line(cmd_lines, pipe_count, i, env) == 1)
			return (0);
		if (check_after_redir(cmd_lines, i, env) == 1)
			return (0);
		if (check_unclosed_quotes(cmd_lines, env, i) == -1)
			return (0);
		if (check_newline(cmd_lines, env, i) == 1)
			return (0);
		cmd_lines[i] = check_null_cmd(cmd_lines, i, env);
		if (cmd_lines[i] == 0)
			return (0);
	}
	return (i);
}

int	check_pipe_repetition(char *temp, t_env **env)
{
	if (*temp == '|' || *temp == '&')
	{
		syntax_error(0, env, *temp);
		return (1);
	}
	while (*temp)
	{
		if (*temp == '\'' || *temp == '"')
			temp = skip_quotes(temp, *temp);
		if (*temp == '|')
		{
			temp++;
			temp = ft_skip_whitespace(temp);
			if (*temp == 0 || *temp == '|')
			{
				syntax_error(0, env, '|');
				return (1);
			}
		}
		temp++;
	}
	return (0);
}
