/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:05 by tkartasl          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/16 12:20:00 by tkartasl         ###   ########.fr       */
=======
/*   Updated: 2024/02/19 12:17:13 by vsavolai         ###   ########.fr       */
>>>>>>> 17cf0669c0e97e7a23821e103e2b59545d53968a
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
