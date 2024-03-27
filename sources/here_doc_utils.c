/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:34:02 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/26 10:23:50 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_h_doc(int fd1, t_redir *temp)
{
    char    *line;

    while(1)
	{
        line = readline("> ");
        if (strncmp(line, temp->filename, ft_strlen(temp->filename) + 1) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, fd1);
    }
}

int    check_h_docs(t_redir *head_redir, int i, int fd1, char **filename)
{
    *filename = "here_doc";
    if (head_redir->index == i)
    {
        if (access(*filename, F_OK) == 0)
            if ((access(*filename, R_OK | W_OK) != 0))
            {
                printf("minishell: here_doc Permission denied\n");
                return (-1);
            }
        fd1 = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
        if (fd1 == -1)
        {
            printf("minishell: here_doc: No such file or directory");
            return (-1);
        }
        run_h_doc(fd1, head_redir);
        close(fd1);
    }
    return (1);
}