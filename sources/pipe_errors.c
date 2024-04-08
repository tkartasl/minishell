/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:20:45 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/04 13:21:23 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pipe_error(int error_nbr, char *cmd)
{
    if (error_nbr == 1)
    {
        ft_putstr_fd("minishell: error allocating memory\n", 2);
        exit(0);
    }
    else if (error_nbr == 2)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putendl_fd(": command not found", 2);
        exit(0);
    }
    else if (error_nbr == 3)
        ft_putstr_fd("minishell: pipe failure\n", 2);
    else if (error_nbr == 4)
        ft_putstr_fd("minishell: fork failure\n", 2);
    else if (error_nbr == 5)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putendl_fd(": No such file or directory", 2);
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
