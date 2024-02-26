/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:15:41 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/26 16:47:28 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

int	get_arg_count(char *cmd_line)
{
	int		count;

	count = 0;
	while (*cmd_line != 0)
	{
		while(*cmd_line != ' ' && *cmd_line != 0)
			cmd_line++;
		cmd_line = ft_skip_whitespace(cmd_line);
		if (*cmd_line != '<' && *cmd_line != '>')
			count++;
		else
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
	return	(count);	
}

char	*get_args(char *cmd_line)
{
	while (*cmd_line != 0)
	{
		while(*cmd_line != ' ' && *cmd_line != 0)
			cmd_line++;
		cmd_line = ft_skip_whitespace(cmd_line);
		if (*cmd_line != '<' && *cmd_line != '>')
			return (cmd_line);
		else
		{
			if ((*cmd_line == '<' || *cmd_line == '>') && (*(cmd_line + 1) == '<' || *(cmd_line + 1) == '>'))
				cmd_line = cmd_line + 2;
			if (*cmd_line == '<' || *cmd_line == '>')
				cmd_line++;
			cmd_line = ft_skip_whitespace(cmd_line);
			while (*cmd_line != 0 && *cmd_line != ' ')
				cmd_line++;
			cmd_line = ft_skip_whitespace(cmd_line);
			if (*cmd_line != '<' && *cmd_line != '>')
				return (cmd_line);
			if ((*cmd_line == '<' || *cmd_line == '>') && (*(cmd_line + 1) == '<' || *(cmd_line + 1) == '>'))
				cmd_line = cmd_line + 2;
			if (*cmd_line == '<' || *cmd_line == '>')
			{	
				cmd_line++;
				cmd_line = ft_skip_whitespace(cmd_line);
			}
		}
	}
	return (0);
}

char	**parse_arguments(char *line)
{
	char	**args;
	char	*temp;
	int		i;
	int		count;
	int		len;

	len = 0;
	temp = line;
	i = 0;
	count = get_arg_count(temp);
	args = malloc((count + 1) * sizeof(char *));
	if (args == 0)
		printf("Error");
	while (i < count)
	{
		line = get_args(line);
		len = get_len(line);
		args[i] = ft_strndup(line, len);
		if (args[i] == 0)
			printf("Error");
		i++;
	}
	args[i] = 0;
	return (args);
}
