/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:34:02 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/25 15:06:10 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_h_doc(int fd1, t_redir *temp)
{
    char    *line;

    ft_printf("limiter: %s\n", temp->filename);
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
    t_redir *temp;

    *filename = "here_doc";
    temp = head_redir;
    if (temp->index == i)
        fd1 = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (fd1 == -1)
        return (-1);
    run_h_doc(fd1, temp);
    close(fd1);
    temp = temp->next;
    return (1);
}