/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:13:47 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/18 15:26:14 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_arrow_lst(char *s, t_redir **new)
{
	while (*s != '\0')
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

void	add_redirs(t_redir **redirs, char **cmd_lines)
{
	int		i;
	t_redir	*new;
	t_redir	*new2;	

	if (!(*redirs))
		return ;
	new = *redirs;
	new2 = *redirs;
	i = 0;
	while (cmd_lines[i] != 0)
	{
		put_arrow_lst(cmd_lines[i], &new);
		if ((*redirs) != 0)
			put_fd_lst(cmd_lines[i], &new2);
		i++;
	}
}

static int	get_redirs(t_redir **redirs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*file;
	char	*temp;

	len = 0;
	i = -1;
	while (cmd_lines[++i] != 0)
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
					return (-1);
				if (build_list(redirs, file, i) < 0)
					return (-1);
			}
		}
	}
	return (0);
}

static int	get_heredocs(t_redir **heredocs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*lim;
	char	*temp;

	len = 0;
	i = -1;
	while (cmd_lines[++i] != 0)
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
					return (-1);
				if (build_list(heredocs, lim, i) < 0)
					return (-1);
			}
		}
	}
	return (0);
}

char	**split_line(char *s, t_env **env, t_redir **hdoc, t_redir **rdir)
{
	char	**cmd_lines;
	int		pipe_count;

	if (*s == 0 || check_pipe_repetition(s, env) == 1)
		return (0);
	cmd_lines = ft_split_remix(s, '|');
	if (cmd_lines == 0)
		return (0);
	pipe_count = get_pipe_count(cmd_lines);
	if (check_syntax(cmd_lines, pipe_count, env) == 0)
		return (0);
	if (get_heredocs(hdoc, cmd_lines) < 0)
	{
		list_free(hdoc, rdir, cmd_lines, 1);
		return (0);
	}
	if (get_redirs(rdir, cmd_lines) < 0)
	{
		list_free(hdoc, rdir, cmd_lines, 1);
		return (0);
	}
	add_redirs(rdir, cmd_lines);
	return (cmd_lines);
}
