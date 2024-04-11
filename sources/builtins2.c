/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:36 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/11 12:04:32 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_to_parent_directory(void)
{
	char	buffer[PATH_MAX + 1];
	char	*path;
	char	*current_d;
	int		len;
	int		len_current;

	path = getcwd(buffer, sizeof(buffer));
	if (ft_strncmp("/Users", path, 7) == 0)
	{
		chdir("/");
		return ;
	}
	if (path == NULL)
	{
		ft_printf("minishell: getcwd: path not found\n");
		return ;
	}
	current_d = ft_strrchr(path, '/');
	len_current = ft_strlen(current_d);
	len = ft_strlen(path) - len_current;
	path = ft_strndup(path, len);
	chdir(path);
}

void	cd(t_cmd_args *cmd_args, t_env **env_table, int *flag)
{
	char	*home;

	*flag = 1;
	if (cmd_args->args[0] == NULL)
	{
		home = ft_get_env("HOME", env_table);
		if (home == NULL)
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
		chdir(home);
	}
	else if (ft_strlen(cmd_args->args[0]) > PATH_MAX)
		print_error(&cmd_args, 1);
	else if (ft_strncmp("..", cmd_args->args[0], 3) == 0)
		change_to_parent_directory();
	else
	{
		if (chdir(cmd_args->args[0]) == -1)
			print_error(&cmd_args, 2);
	}
}

void	ft_exit(char *status, t_env **env_table, t_cmd_args **cmd_args)
{
	char	*temp;
	int		i;

	i = 0;
	temp = status;
	while (*temp != 0 && ft_isdigit(*temp) == 1)
		temp++;
	if (*temp == 0)
		i = ft_atoi(status);
	ft_putstr_fd("exit\n", 1);
	free_env_table(env_table);
	free_struct_array(cmd_args);
	exit(i);
}

void	env(t_env **env_table, int *flag)
{
	int	i;

	i = 0;
	*flag = 1;
	if (ft_get_env("PATH", env_table) == NULL)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return ;
	}
	while (i < TABLE_SIZE)
	{
		if (env_table[i] != NULL && env_table[i] != DELETED_NODE)
			ft_printf("%s%s\n", env_table[i]->name, env_table[i]->value);
		i++;
	}
}

void	export_env(t_env **env, int *flag)
{
	int	i;

	i = 0;
	*flag = 1;
	if (ft_get_env("PATH", env) == NULL)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return ;
	}
	while (i < TABLE_SIZE)
	{
		if (env[i] != NULL && env[i] != DELETED_NODE)
			ft_printf("declare -x %s%s\n", env[i]->name, env[i]->value);
		i++;
	}
}
