/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:26:12 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/01 14:11:30 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    put_arrow_lst(char *line, t_redir **new, int j)
{
    while(line[j] != '\0')
    {
        if (line[j] == '<' && line[j + 1] == '<')
            j = j + 2;
        if (line[j] == '<')
        {
            (*new)->arrow = '<';
            (*new) = (*new)->next;
        }
        else if (line[j] == '>')
        {
            if (line[j + 1] == '>')
            {
                (*new)->arrow = '!';
				j++;
            }
            else
                (*new)->arrow = '>';
            (*new) = (*new)->next;
        }
		
        j++;
    }
}

void    add_redirs(t_redir **redirs, char **cmd_lines)
{
    int 		i;
    int 		j;
    t_redir    *new;

    new = *redirs;
    i =    0;
    while(cmd_lines[i] != 0)
    {
        j = 0;
        put_arrow_lst(cmd_lines[i], &new, j);
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

void	parse_line(char	*line)
{
	char		**cmd_lines;
	int			pipe_count;
	t_redir		*heredocs;
	t_redir		*redirs;
	t_cmd_args	**cmd_args;
	
	heredocs = 0;
	redirs = 0;
	cmd_lines = ft_split(line, '|');
    if (cmd_lines == 0)
        return ;
	pipe_count = get_pipe_count(cmd_lines);
	if (check_syntax(cmd_lines, pipe_count) == 0)
        return ;
	get_heredocs(&heredocs, &redirs, cmd_lines);
	get_redirs(&redirs, &heredocs, cmd_lines);
	add_redirs(&redirs, cmd_lines);
	cmd_args = get_array(&redirs, &heredocs, cmd_lines, pipe_count);
}
