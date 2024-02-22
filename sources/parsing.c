/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:26:12 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/22 12:21:44 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_heredocs(t_redir **heredocs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*lim;

	lim = 0;
	len = 0;
	i = 0;
	while (i < 3)
	{
		while (*cmd_lines[i] != 0)
		{
			cmd_lines[i] = find_redir(&*cmd_lines[i]);
			if (*cmd_lines[i] != 0)
			{
				len = get_len(&*cmd_lines[i]);
				lim = ft_strndup(&*cmd_lines[i], len);
				if (lim == 0)
					printf("Error\n");
				build_list(heredocs, lim, i);
			}	
		}
		i++;
	}
}

t_cmd_args	*get_pipelines(char *line, int pipe_count)
{
	t_cmd_args	*cmd_line;

	ft_memset(cmd_line, 0 , sizeof(t_cmd_args));
	cmd_line->pipe_count = pipe_count;
}

void	parse_line(char	*line)
{
	char		**cmd_lines;
	int			pipe_count;
	int			i;
	t_cmd_args	**struct_array;
	
	i = 0;
	pipe_count = 0;
	cmd_lines = ft_split(line, '|');
	while (cmd_lines[pipe_count] != 0)
		pipe_count++;
	struct_array = malloc(pipe_count * sizeof(t_cmd_args));
	if (struct_array == NULL)
	{
		ft_free_pointer_array(cmd_lines);
		exit (EXIT_FAILURE);
	}
	while (cmd_lines[i] != 0)
	{
		struct_array[i] = get_pipelines(cmd_lines[i]);
		i++;
	}
}
