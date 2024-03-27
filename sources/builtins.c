/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:05 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/26 09:10:28 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args, int fd)
{
	int	i;	
	int	j;
	
	i = 0;
	j = 0;
	while (args[i] != 0)
	{
		ft_putstr_fd(args[i], fd);
		i++;
	}
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
