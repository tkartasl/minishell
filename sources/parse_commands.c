/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:31:42 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/07 09:04:31 by tkartasl         ###   ########.fr       */
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
		while(*cmd_line != ' ' && *cmd_line != 0)
			cmd_line++;
		cmd_line = ft_skip_whitespace(cmd_line);
		if (*cmd_line != '<' && *cmd_line != '>')
			break ;
	}
	if (*cmd_line == '\'' || *cmd_line == '\"')
		len = get_quotes_len(cmd_line, *cmd_line);
	if (len == 0)
	len = get_len(cmd_line);
	cmd = ft_strndup(cmd_line, len);
	if (cmd == 0)
		return (0);
	return (cmd);
}

char	*parse_command(char *cmd_line)
{
	int		len;
	char	*cmd;

	len = 0;
	cmd = 0;
	cmd_line = ft_skip_whitespace(cmd_line);
	if (*cmd_line != '<' && *cmd_line != '>')
	{
		if (*cmd_line == '\'' || *cmd_line == '\"')
			len = get_quotes_len(cmd_line, *cmd_line);
		if (len == 0)
		len = get_len(cmd_line);
		cmd = ft_strndup(cmd_line, len);
		if (cmd == 0)
			return (0);
		return (cmd);
	}
	else
		cmd = find_cmd(cmd_line);
	return (cmd);	
}

t_cmd_args	*struct_new(t_redir **redir, t_redir **hdoc, int pipe)
{
	t_cmd_args	*new;

	new = malloc(sizeof(t_cmd_args));
	if (new == 0)
		return (0);
	new->head_hdocs = hdoc;
	new->head_redir = redir;
	new->pipe_count = pipe;
	new->cmd = 0;
	new->args = 0;
	return (new);
}	



t_cmd_args    *get_structs(t_redir **redir, t_redir **hdoc, char *line, int pc)
{
    t_cmd_args    *new;
    char        *temp;
    int            len;
    char        *temp2;

  	new = struct_new(redir, hdoc, pc);
	if (new == 0)
		return (0);
	len = ft_strlen(line);
	temp = line;
	new->cmd = parse_command(temp);
	if (new->cmd == 0)
		return (0);
	temp = ft_strnstr(line, new->cmd, len);
	temp2 = temp;
	temp = skip_cmd(temp);
    temp = ft_skip_whitespace(temp);
    new->args = parse_arguments(temp, temp2);
	if (new->args == 0)
		return (0);
    return (new);
}

t_cmd_args	**get_array(t_redir **redir, t_redir **hdoc, char **line, int pipe)
{
	t_cmd_args	**array;
	int			i;

	i = 0;
	array = malloc((pipe + 1) * sizeof(t_cmd_args *));
	if (array == 0)
		list_build_error(hdoc, redir, line);
	while (line[i] != 0)
	{
		array[i] = get_structs(redir, hdoc, line[i], pipe);
		if (array[i] == 0)
		{
			free_struct_array(array);
			ft_free_pointer_array(line);
		}
		i++;
	}
	array[i] = 0;
	ft_free_pointer_array(line);
	return (array);
}
