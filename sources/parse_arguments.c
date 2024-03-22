/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:15:41 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/22 12:52:46 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_next_arg(char *cmd_line)
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
	return (cmd_line);
}

void	get_arg_count(char *cmd_line, int *count)
{
	while (*cmd_line != 0)
	{
		if (ft_isdigit(*cmd_line) == 1 && *(cmd_line - 1) == ' ')
	    {
			while (*cmd_line != '<' && *cmd_line != '>' && *cmd_line != ' '
				&& *cmd_line != 0 && ft_isdigit(*cmd_line) == 1)
				cmd_line++;
		}
		if (*cmd_line != '<' && *cmd_line != '>' && *cmd_line != 0)
		{
			*count += 1;
            cmd_line = skip_arg(cmd_line);
			cmd_line = ft_skip_whitespace(cmd_line);
		}
		else
			cmd_line = find_next_arg(cmd_line);
	}
}

char	*get_args(char *cmd_line, int i)
{
	while (*cmd_line != 0)
	{
		cmd_line = ft_skip_whitespace(cmd_line);
        if (i != 0)
		{  
            cmd_line = skip_arg(cmd_line);
		    cmd_line = ft_skip_whitespace(cmd_line);
        }
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
		line2 = get_args(line2, i);
		len = get_arg_len(line2);	
		args[i] = ft_strndup(line2, len);
		if (args[i] == 0)
			return (0);
		i++;
	}
	args[i] = 0;
	return (args);
}
