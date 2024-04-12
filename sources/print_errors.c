/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:02:18 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/12 11:47:10 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_filename(char *file, int *flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	*flag = 1;
}

void	print_error(t_cmd_args **arr, int flag)
{
	if (flag == -1)
		ft_putendl_fd("minishell: error allocating memory", 2);
	if (flag == 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((*arr)->args[0], 2);
		ft_putendl_fd(": File name too long", 2);
	}
	if (flag == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((*arr)->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

void	export_error(char *str, t_env **env_table)
{
	change_cmd_status(env_table, 256);
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'", 2);
	ft_putendl_fd(": not a valid identifier", 2);
}

int check_flag(int flag, char **cmd)
{
    if (flag == 3 || flag == 4)
    {
        pipe_error(flag, NULL, cmd);
        return (-1);
    }
    if (cmd == NULL)
        return (-1);
    return (1);
}
