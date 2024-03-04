/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:15:41 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/04 12:42:23 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_arg_count(char *cmd_line, int *count)
{
	while (*cmd_line != 0)
	{
		if (*cmd_line != '<' && *cmd_line != '>' && *cmd_line != 0)
		{
			*count += 1;
			if (*cmd_line == '\'' || *cmd_line == '\"')
				cmd_line = skip_quotes(cmd_line, *cmd_line);
			else
			{
				while (*cmd_line != ' ' && *cmd_line != 0)
					cmd_line++;
			}
			cmd_line = ft_skip_whitespace(cmd_line);
		}
		else
		{
			while (*cmd_line != 0 && (*cmd_line == '>' || *cmd_line == '<'))
			{
				if ((*cmd_line == '<' || *cmd_line == '>') && (*(cmd_line + 1) == '<' || *(cmd_line + 1) == '>'))
					cmd_line = cmd_line + 2;
				if (*cmd_line == '<' || *cmd_line == '>')
					cmd_line++;
				cmd_line = ft_skip_whitespace(cmd_line);
				while (*cmd_line != 0 && *cmd_line != ' ')
					cmd_line++;
				cmd_line = ft_skip_whitespace(cmd_line);
			}
		}
	}
}

char	*get_args(char *cmd_line)
{
	while (*cmd_line != 0)
	{
		if (*cmd_line == '\'' || *cmd_line == '\"')
			cmd_line = skip_quotes(cmd_line, *cmd_line);
		else
		{
			while(*cmd_line != ' ' && *cmd_line != 0)
				cmd_line++;
		}
		cmd_line = ft_skip_whitespace(cmd_line);
		if (*cmd_line != '<' && *cmd_line != '>')
			return (cmd_line);
		else
		{
			cmd_line = skip_redirs(cmd_line);
			while (*cmd_line != 0 && *cmd_line != ' ')
				cmd_line++;
			cmd_line = ft_skip_whitespace(cmd_line);
			if (*cmd_line != '<' && *cmd_line != '>')
				return (cmd_line);
			cmd_line = skip_redirs(cmd_line);
		}
	}
	return (0);
}

char	**parse_arguments(char *line, char *line2)
{
	char	**args;
	int		i;
	int		count;
	int		len;

	count = 0;
	len = 0;
	i = 0;
	get_arg_count(line, &count);
	args = malloc((count + 1) * sizeof(char *));
	if (args == 0)
		return (0);
	while (i < count)
	{
		line2 = get_args(line2);
		len = get_len(line2);
		if (*line2 == '\'' || *line2 == '\"')
			len = get_quotes_len(line2, *line2);
		args[i] = ft_strndup(line2, len);
		if (args[i] == 0)
			printf("Error");
		i++;
	}
	args[i] = 0;
	return (args);
}
