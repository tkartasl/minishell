/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:26:12 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/07 10:49:08 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    put_arrow_lst(char *line, t_redir **new)
{
    while(*line != '\0')
    {
		if (*line == '\'' || *line == '\"')
			line = skip_quotes(line, *line);
        if (*line == '<' && *(line + 1) == '<')
            line = line + 2;
        if (*line == '<')
        {
            (*new)->arrow = '<';
            (*new) = (*new)->next;
        }
        else if (*line == '>')
        {
            if (*(line + 1) == '>')
            {
                (*new)->arrow = '!';
				line++;
            }
            else
                (*new)->arrow = '>';
            (*new) = (*new)->next;
        }
		line++;
    }
}

void    add_redirs(t_redir **redirs, char **cmd_lines)
{
    int 		i;
    t_redir    *new;

    new = *redirs;
    i =	0;
    while(cmd_lines[i] != 0)
    {
        put_arrow_lst(cmd_lines[i], &new);
        i++;
    }
}

void	get_redirs(t_redir **redirs, t_redir **heredocs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*file;
	char	*temp;

	len = 0;
	i = 0;
	while (cmd_lines[i] != 0)
	{
		temp = cmd_lines[i];
		while (*temp != 0)
		{
			temp = find_redir(temp);
			if (*temp != 0)
			{
				len = get_len(temp);
				file = ft_strndup(temp, len);
				if (file == 0)
					list_build_error(heredocs, redirs, cmd_lines);
				if (build_list(redirs, file, i) < 0)
					list_build_error(heredocs, redirs, cmd_lines);
			}	
		}
		i++;
	}
}

void	get_heredocs(t_redir **heredocs, t_redir **redirs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*lim;
	char	*temp;

	len = 0;
	i = 0;
	while (cmd_lines[i] != 0)
	{
		temp = cmd_lines[i];
		while (*temp != 0)
		{
			temp = find_limiter(temp);
			if (*temp != 0)
			{
				len = get_len(temp);
				lim = ft_strndup(temp, len);
				if (lim == 0)
					list_build_error(heredocs, redirs, cmd_lines);
				if (build_list(heredocs, lim, i) < 0)
					list_build_error(heredocs, redirs, cmd_lines);
			}
		}
		i++;
	}
}

void	parse_line(char	*line, char **envp)
{
	char		**cmd_lines;
	int			pipe_count;
	t_redir		*heredocs;
	t_redir		*redirs;
	t_cmd_args	**cmd_args;
	
	heredocs = 0;
	redirs = 0;
    if (check_pipe_repetition(line) == 1)
        return ;
	cmd_lines = ft_split_remix(line, '|');
    if (cmd_lines == 0)
        return ;
	pipe_count = get_pipe_count(cmd_lines);
	if (check_syntax(cmd_lines, pipe_count) == 0)
        return ;
	get_heredocs(&heredocs, &redirs, cmd_lines);
	get_redirs(&redirs, &heredocs, cmd_lines);
	add_redirs(&redirs, cmd_lines);
	cmd_args = get_array(&redirs, &heredocs, cmd_lines, pipe_count);
    if (cmd_args == 0)
        return ;
    int i = 0;
    int j;
    while(cmd_args[i])
    {
        printf("Command: %s\n", cmd_args[i]->cmd);
        j = 0;
        while(cmd_args[i]->args[j])
        {
            printf("command %d argument: %s\n", i, cmd_args[i]->args[j]);
            j++;
        }
        printf("pipe count: %d\n", cmd_args[i]->pipe_count);
        i++;
    }

    i = 0;
    while(cmd_args[i]->head_redir[i])
    {
        write(2, "loop start\n", 11);
        printf("redir nbr: %d\n", cmd_args[i]->head_redir[i]->index);
        printf("redir: %c\n", cmd_args[i]->head_redir[i]->arrow);
        printf("filename: %s\n", cmd_args[i]->head_redir[i]->filename);
        cmd_args[i]->head_redir[i] = cmd_args[i]->head_redir[i]->next;
        write(2, "loop end\n", 9);
    }

    i = 0;
    while(cmd_args[i]->head_hdocs[i])
    {
        write(2, "here_doc start\n", 15);
        printf("redir nbr: %d\n", cmd_args[i]->head_hdocs[i]->index);
        printf("redir: %c\n", cmd_args[i]->head_hdocs[i]->arrow);
        printf("filename: %s\n", cmd_args[i]->head_hdocs[i]->filename);
        cmd_args[i]->head_hdocs[i] = cmd_args[i]->head_hdocs[i]->next;
        write(2, "here_doc end\n", 13);
    }
	run_commands(cmd_args, pipe_count, envp);
}
