/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:29:52 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/25 14:49:02 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_fd_rights(char *filename, int flag)
{
    if (flag == 1)
    {
        if (access(filename, R_OK) != 0)
        {
            printf("minishell: %s: Permission denied\n", filename);
            return (-1);
        }
        else if (flag == 2)
        {
            if (access(filename, F_OK) == 0)
                if (access(filename, W_OK) != 0)
                {
                    printf("minishell: %s: Permission denied\n", filename);
                    return (-1);
                }
        }
    }
    return (0);
}

int check_open_fd(char  *filename, char arrow, int fd, int flag)
{
    if (flag == 1)
    {
        fd = open(filename, O_RDONLY, 0777);
        if (fd == -1)
        {
            printf("minishell: %s: No such file or directory", filename);
            return (-1);
        }
    }
    else if (flag == 2)
    {
        if (arrow == '>')
            fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
        else if (arrow == '!')
            fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (fd == -1)
        {
            printf("minishell: %s: No such file or directory", filename);
            return (-1);
        }
    }
    return (fd);
}

void    check_in_redir(t_redir **head_redir, int i, int fd1)
{
    t_redir *temp;
    char    *filename;

    filename = NULL;
    temp = *head_redir;
    while(temp != 0)
    {
        if (temp->index == i && temp->arrow == '<')
        {
            filename = temp->filename;
            if (check_fd_rights(filename, 1) == -1)
                return ;
        }
        else if (temp->index == i && temp->arrow == 'h')
            if (check_h_docs(temp, i, fd1, &filename) == -1)
                return ;
        temp = temp->next;
    }
    if (filename != NULL)
    {
        fd1 = check_open_fd(filename, '<', fd1, 1);
        if (fd1 == -1)
            return ;
        dup2(fd1, 0);
    }
}

void    check_out_redir(t_redir **head_redir, int i, int fd2)
{
     t_redir *temp;
    char    *filename;
    char    arrow;

    filename = NULL;
    temp = *head_redir;
    while(temp != 0)
    {
        if ((temp->index == i) && ((temp->arrow == '>') || (temp->arrow == '!')))
        {
            filename = temp->filename;
            arrow = temp->arrow;
            if (check_fd_rights(filename, 2) == -1)
                return ;
        }
        temp = temp->next;
    }
    if (filename != NULL)
    {
        fd2 = check_open_fd(filename, arrow, fd2, 2);
        if (fd2 == -1)
            return ;
        dup2(fd2, 1);
    }
    
}
