/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:34:02 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/03 16:44:28 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_h_doc(int *pipe_fd, t_redir *temp)
{
    char    *line;
    char    *limiter;

    limiter = ft_strjoin(temp->filename, "\n");
    if (limiter == NULL)
        return (-1);
    while(1)
	{
        write(temp->original_output, "> ", 2);
        line = get_next_line(temp->original_input);
        if (line == NULL)
            break;
        if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
            break;
        ft_putstr_fd(line, pipe_fd[1]);
        free(line);
    }
    free(line);
    free(limiter);
    return (1);
}

int    check_h_docs(t_redir *head_redir, int i, char **filename)
{
    int     pipe_fd[2];

    *filename = "here_doc";
    if (head_redir->index == i)
    {
        if (pipe(pipe_fd) == -1)
        {
            ft_putstr_fd("minishell: pipe failure\n", 2);
            return (-1);
        }
        if (run_h_doc(pipe_fd, head_redir) == -1)
        {
            close(pipe_fd[0]);
		    close(pipe_fd[1]);
            ft_putstr_fd("minishell: error allocating memory\n", 2);
            return (-1);
        }
        close(pipe_fd[1]);
        return(pipe_fd[0]);
    }
    return (1);
}