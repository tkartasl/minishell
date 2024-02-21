/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:26:12 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/19 14:59:14 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_args	*get_pipelines(char *line)
{
	t_cmd_args	*cmd_line;

	ft_memset(cmd_line, 0 , sizeof(t_cmd_args));
	
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
