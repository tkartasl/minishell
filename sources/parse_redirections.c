/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:13:47 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/27 09:13:28 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    put_arrow_lst(char *s, t_redir **new)
{
    while(*s != '\0')
    {
		while ((*s == '\'' || *s == '"') && *s != 0)
			s = skip_quotes(s, *s);
        if (*s == '<')
        {
            if (*(s + 1) == '<')
                (*new)->arrow = 'h';
            else
                (*new)->arrow = '<';
            (*new) = (*new)->next;
        }
        else if (*s == '>')
        {
            if (*(s + 1) == '>')
                (*new)->arrow = '!';	
            else
                (*new)->arrow = '>';
            (*new) = (*new)->next;
        }
        if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s + 1) == '<'))
                s++;
		if (*s != 0)
			s++;
    }
}

void    add_redirs(t_redir **redirs, char **cmd_lines)
{
    int		i;
    t_redir	*new;
	t_redir	*new2;	
	
    new = *redirs;
	new2 = *redirs;
    i =	0;
    while(cmd_lines[i] != 0)
    {
        put_arrow_lst(cmd_lines[i], &new);
		if ((*redirs) != 0)
			put_fd_lst(cmd_lines[i], &new2);
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

void	parse_line(char	*line, t_env **env_table)
{
	char		**cmd_lines;
	int			pipe_count;
	t_redir		*heredocs;
	t_redir		*redirs;
	t_cmd_args	**cmd_args;
	
    (void)env_table;
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
    if (get_envs(cmd_args, env_table) == 0)
		ft_printf("ERROR");
	/*
    int i = 0;
    int j;
    t_cmd_args	**temp;
    temp = cmd_args;
    while(temp[i])
    {
        printf("Command: %s\n", temp[i]->cmd);
        j = 0;
        while(temp[i]->args[j])
        {
            printf("command %d argument: %s\n", i, temp[i]->args[j]);
            j++;
        }
        printf("pipe count: %d\n", temp[i]->pipe_count);
        i++;
    }
    i = 0;
    while(temp[i]->head_redir[i])
    {
        write(2, "loop start\n", 11);
        printf("redir nbr: %d\n", temp[i]->head_redir[i]->index);
        printf("redir: %c\n", temp[i]->head_redir[i]->arrow);
        printf("filename: %s\n", temp[i]->head_redir[i]->filename);
		printf("fd: %d\n", temp[i]->head_redir[i]->fd);
		printf("flag: %d\n", temp[i]->head_redir[i]->flag);
        temp[i]->head_redir[i] = temp[i]->head_redir[i]->next;
        write(2, "loop end\n", 9);
    }

    i = 0;
    while(temp[i]->head_hdocs[i])
    {
        write(2, "here_doc start\n", 15);
        printf("redir nbr: %d\n", temp[i]->head_hdocs[i]->index);
        printf("redir: %c\n", temp[i]->head_hdocs[i]->arrow);
        printf("filename: %s\n", temp[i]->head_hdocs[i]->filename);
        temp[i]->head_hdocs[i] = temp[i]->head_hdocs[i]->next;
        write(2, "here_doc end\n", 13);
    }
    i = 0;*/
    //printf("enviroment variables\n");
    check_cmds(cmd_args, env_table);
}
