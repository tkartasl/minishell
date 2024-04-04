/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:29:52 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/03 15:50:27 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_fd_rights(t_redir *redir, char **filename, char *arrow, int flag)
{
    if (flag == 1)
    {
        if (access(redir->filename, R_OK) != 0)
        {
            printf("minishell: %s: Permission denied\n", *filename);
            return (-1);
        }
        *filename = redir->filename;
    }
    else if (flag == 2)
    {
        if (access(redir->filename, F_OK) == 0)
            if (access(redir->filename, W_OK) != 0)
            {
                printf("minishell: %s: Permission denied\n", *filename);
                return (-1);
            }
        *filename = redir->filename;
        *arrow = redir->arrow;
    }
    return (0);
}

int check_open_fd(char  *filename, char arrow, int fd, int flag)
{
    if (flag == 1)
    {
        if (ft_strncmp(filename, "here_doc", 9) != 0)
            fd = open(filename, O_RDONLY, 0777);
        if (fd == -1)
        {
            printf("1minishell: %s: No such file or directory\n", filename);
            return (-1);
        }
        dup2(fd, 0);
    }
    else if (flag == 2)
    {
        if (arrow == '>')
            fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
        else if (arrow == '!')
            fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (fd == -1)
        {
            printf("minishell: %s: No such file or directory\n", filename);
            return (-1);
        }
        dup2(fd, 1);
    }
    return (fd);
}

int check_fd_redirection(t_redir *temp, char arrow, int fd)
{
        if (temp->flag == 1 && temp->arrow == arrow)
        {
            if (temp->fd > 255)
            {
                if (temp->fd > 2147483647)
                    printf("minishell: file descriptor out of reach\n");
                else
                    printf("minishell: bad file descriptor\n");
                return (-1);
            }
            fd = open(temp->filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
            if (fd == -1)
            {
                printf("minishell: %s: can't open file", temp->filename);
                return (-1);
            }
            dup2(fd, temp->fd);
            return (1);
        }
        return (0);
    }

int    check_in_redir(t_redir **head_redir, int i, int fd1)
{
    t_redir *temp;
    char    *filename;
    int     flag;

    filename = NULL;
    temp = *head_redir;
    while(temp != 0)
    {
        flag = 0;
        if (temp->index == i && temp->arrow == '<')
            if (check_fd_rights(temp, &filename, NULL, 1) == -1)
                return (-1);
        if (temp->index == i && temp->arrow == 'h')
            fd1 = check_h_docs(temp, i, &filename);
        if (fd1 == -1)
            return (-1);
        flag = check_fd_redirection(temp, '<', fd1);
        if (flag == -1)
            return (-1);
        temp = temp->next;
    }
    if (filename != NULL && flag == 0)
        if (check_open_fd(filename, '<', fd1, 1) == -1)
            return (-1);
    return (0);
}

int    check_out_redir(t_redir **head_redir, int i, int fd2, int *fl)
{
     t_redir *temp;
    char    *filename;
    char    arrow;
    int     flag;

    filename = NULL;
    temp = *head_redir;
    while(temp != 0)
    {
        flag = 0;
        if ((temp->index == i) && ((temp->arrow == '>') || (temp->arrow == '!')))
            if (check_fd_rights(temp, &filename, &arrow, 2) == -1)
                return (-1);
        flag = check_fd_redirection(temp, '>', fd2);
        if (flag == -1)
            return (-1);
        temp = temp->next;
    }
    if (filename != NULL && flag == 0)
    {
        if (check_open_fd(filename, arrow, fd2, 2) == -1)
            return (-1);
        *fl = 1;
    }
    return (0);
}
