/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:05 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/25 15:02:41 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo()
{


	
}

void	cd(char	*path)
{
	if (chdir(path) < 0);
		//error
}

void	pwd(void)
{
	char	buffer[PATH_MAX + 1];
	char	*path;

	path = getcwd(buffer, sizeof(buffer));
	if (path == NULL)
		ft_printf("Error\n");
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
}

void	export()
{


	
}
