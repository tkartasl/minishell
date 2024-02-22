/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:26:12 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/22 17:00:24 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_redirs(t_redir **redirs, char **cmd_lines)
{
    int 		i;
    int 		j;
    t_redir    *new;

    new = *redirs;
    i =    0;
    while(i < 4)
    {
        j = 0;
        while(cmd_lines[i][j] != '\0')
        {
            if (cmd_lines[i][j] == '<')
            {
                new->arrow = '<';
                new = new->next;
            }
            else if (cmd_lines[i][j] == '>')
            {
                if (cmd_lines[i][j + 1] == '>')
                {
                    new->arrow = '!';
                    j++;
                }
                else
                    new->arrow = '>';
                new = new->next;
            }
            j++;
        }
        i++;
    }
}

void	get_heredocs(t_redir **heredocs, char **cmd_lines)
{
	int		i;
	int		len;
	char	*lim;
	char	*temp;

	lim = 0;
	len = 0;
	i = 0;
	while (i < 4)
	{
		temp = cmd_lines[i];
		while (*temp != 0)
		{
			temp = find_redir(temp);
			if (*temp != 0)
			{
				len = get_len(temp);
				lim = ft_strndup(temp, len);
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
