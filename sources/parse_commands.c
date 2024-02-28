/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:31:42 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/28 09:25:14 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_cmd(char *cmd_line)
{
	char	*cmd;
	int		len;

	len = 0;
	while (1)
	{
		cmd_line = skip_redirs(cmd_line);
		while(*cmd_line != ' ' && cmd_line != 0)
			cmd_line++;
		cmd_line = ft_skip_whitespace(cmd_line);
		if (*cmd_line != '<' && *cmd_line != '>')
			break ;
	}
	len = get_len(cmd_line);
	cmd = ft_strndup(cmd_line, len);
	if (cmd == 0)
		printf("error\n");
	return	(cmd);	
}

char	*parse_command(char *cmd_line)
{
	int		len;
	char	*cmd;

	len = 0;
	cmd = 0;
	if (*cmd_line != '<' && *cmd_line != '>')
	{
		cmd_line = ft_skip_whitespace(cmd_line);
		len = get_len(cmd_line);
		cmd = ft_strndup(cmd_line, len);
		if (cmd == 0)
			//Error
		return (cmd);
	}
	else
		cmd = find_cmd(cmd_line);
	return (cmd);	
}

t_cmd_args	*get_structs(t_redir **redir, t_redir **hdoc, char *line, int pipe)
{
	t_cmd_args	*line;
	char		*temp;
	int			len;
	char		*temp2;
	
	len = ft_strlen(line);
	temp = line;
	ft_memset(line, 0, sizeof(t_cmd_args));
	line->head_hdocs = hdoc;
	line->head_redir = redir;
	line->pipe_count = pipe;
	line->cmd = parse_command(temp);
	temp = ft_strnstr(line, line->cmd, len);
	temp2 = temp;
	while(*temp != ' ' && *temp != 0)
			temp++;
	temp = ft_skip_whitespace(temp);
	line->args = parse_arguments(temp, temp2);
	return (line);	
}

t_cmd_args	**get_array(t_redir **redir, t_redir **hdoc, char **line, int pipe)
{
	t_cmd_args	**array;
	int			i;
	
	array = malloc((pipe + 1) * sizeof(t_cmd_args *))
	if (line == 0)
		//Error
	while (line[i] != 0)
	{
		array[i] = get_structs(redir, hdoc, &line[i], pipe);
		i++;
	}
	
	return (array);
}
