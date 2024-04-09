/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:20:45 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/09 16:51:35 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pipe_error(int error_nbr, char *cmd, char **cmds)
{
    if (error_nbr == 1)
    {
        ft_putstr_fd("minishell: error allocating memory\n", 2);
        exit(0);
    }
    else if (error_nbr == 3)
    {
        ft_putstr_fd("minishell: pipe failure\n", 2);
        ft_free_pointer_array(cmds);
    }
    else if (error_nbr == 4)
    {
        ft_putstr_fd("minishell: fork failure\n", 2);
        ft_free_pointer_array(cmds);
    }
    else if (error_nbr == 5)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putendl_fd(": No such file or directory", 2);
        ft_free_pointer_array(cmds);
        exit(0);
    }
}

void    pipe_error_cmd(char *cmd, char **cmds)
{
    int len;

    len = ft_strlen(cmd);
    if (cmd[len - 1] != '/')
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putendl_fd(": command not found", 2);
        ft_free_pointer_array(cmds);
        exit(0);
    }
    else
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putendl_fd(": No such file or directory", 2);
        ft_free_pointer_array(cmds);
        exit(0);
    }
}

void    file_error(int error_nbr, char *cmd)
{
    if (error_nbr == 1)
    {
        ft_putstr_fd("minishell:", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": permission denied\n", 2);
        exit(0);
    }
    else if (error_nbr == 2)
    {
        ft_putstr_fd("minishell:", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": is a directory\n", 2);
        exit(0);
    }
}
