/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:36 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/30 08:26:47 by vsavolai         ###   ########.fr       */
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
		ft_putstr_fd("minishell: getcwd: path not found\n", 2);
		return ;
	}
	current_d = ft_strrchr(path, '/');
	len_current = ft_strlen(current_d);
	len = ft_strlen(path) - len_current;
	path = ft_strndup(path, len);
	chdir(path);
	free(path);
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
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		chdir(home);
	}
	else if (ft_strlen(cmd_args->args[0]) > PATH_MAX)
		print_error(&cmd_args, 1, env_table);
	else if (ft_strncmp("..", cmd_args->args[0], 3) == 0)
		change_to_parent_directory();
	else
	{
		if (chdir(cmd_args->args[0]) == -1)
			print_error(&cmd_args, 2, env_table);
	}
	if (update_table(env_table) == -1)
		return ;
	change_cmd_status(env_table, 0);
}

void	ft_exit(t_env **env_table, t_cmd_args **c, int flag)
{
	int	i;

	i = 0;
	flag = 0;
	ft_putstr_fd("exit", 1);
	if ((*c)->args[0] != NULL)
	{
		while ((*c)->args[i])
		{
			if (ft_isdigit((*c)->args[0][i]) == 0)
			{
				ft_printf(": ");
				ft_printf("%s:  numeric argument required", (*c)->args[0], 1);
				flag = 255;
				break ;
			}
			i++;
			flag = ft_atoi((*c)->args[0]);
		}
	}
	ft_putstr_fd("\n", 1);
	rl_clear_history();
	free_env_table(env_table);
	free_struct_array(c);
	exit(flag);
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
		if (env_table[i] != NULL && env_table[i] != (t_env *)(DELETED_NODE))
			ft_printf("%s%s\n", env_table[i]->name, env_table[i]->value);
		i++;
	}
	change_cmd_status(env_table, 0);
}

void	export_env(t_env **env, int *flag)
{
	int	i;

	i = 0;
	*flag = 1;
	while (i < TABLE_SIZE)
	{
		if (env[i] != NULL && env[i] != (t_env *)(DELETED_NODE))
		{
			ft_printf("declare -x %s", env[i]->name);
			ft_printf("\"");
			ft_printf("%s", env[i]->value);
			ft_printf("\"");
			ft_printf("\n");
		}
		i++;
	}
}
