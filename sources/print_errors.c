/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:02:18 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/11 12:05:52 by tkartasl         ###   ########.fr       */
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
	free_struct_array(arr);
}
