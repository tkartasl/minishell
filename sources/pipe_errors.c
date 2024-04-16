/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:20:45 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/15 11:51:41 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_error(int error_nbr, char *cmd, char **cmds)
{
	if (error_nbr == 1)
	{
		ft_putstr_fd("minishell: error allocating memory\n", 2);
		exit(1);
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
		ft_free_pointer_array(cmds);
		exit(1);
	}
	else if (error_nbr == 6)
	{
		free(cmd);
		exit(0);
	}
}

void	pipe_error_cmd(char *cmd, char **cmds)
{
	if (ft_strchr(cmd, '/') == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		ft_free_pointer_array(cmds);
		exit(127);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free_pointer_array(cmds);
		exit(1);
	}
}

void	file_error(int error_nbr, char *cmd)
{
	if (error_nbr == 1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
		exit(1);
	}
	else if (error_nbr == 2)
	{
		write(2, "t\n", 2);
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	else if (error_nbr == 3)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Not a directory \n", 2);
		exit(1);
	}
}
