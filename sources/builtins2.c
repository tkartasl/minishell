/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:36 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/09 17:10:18 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    change_to_parent_directory(void)
{
    char    buffer[PATH_MAX + 1];
    char    *path;
    char    *current_d;
    int     len;
    int     len_current;

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
    char    *home;
    
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
        printf("minishell: cd: %s: File name too long\n", cmd_args->args[0]);
    else if (ft_strncmp("..", cmd_args->args[0], 3) == 0)
        change_to_parent_directory();
    else
    {
        if (chdir(cmd_args->args[0]) == -1)
            printf("minishell: cd: %s: No such file or directory\n",
            cmd_args->args[0]);
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
	
    printf("exit\n");
    free_env_table(env_table);
    free_struct_array(cmd_args);
	exit(i);
}

void    env(t_env **env_table, int *flag)
{
    int     i;

    i = 0;
    *flag = 1;
    if (ft_get_env("PATH", env_table) == NULL)
    {
        printf("minishell: env: No such file or directory\n");
        return ;
    }
    while(i < TABLE_SIZE)
    {
        if (env_table[i] != NULL && env_table[i] != DELETED_NODE)
            printf("%s%s\n", env_table[i]->name, env_table[i]->value);
        i++;
    }
}

void    export_env(t_env **env_table, int *flag)
{
    int     i;

    i = 0;
    *flag = 1;
    if (ft_get_env("PATH", env_table) == NULL)
    {
        printf("minishell: env: No such file or directory\n");
        return ;
    }
    while(i < TABLE_SIZE)
    {
        if (env_table[i] != NULL && env_table[i] != DELETED_NODE)
            printf("declare -x %s%s\n", env_table[i]->name, env_table[i]->value);
        i++;
    }
}