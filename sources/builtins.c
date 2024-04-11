/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:05 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/10 13:44:45 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args, int fd, int *flag)
{
	int	i;	
	int	j;
    int flag_nl;
	
    *flag = 1;
    flag_nl = 0;
	i = 0;
	j = 0;
    if (!(ft_strncmp(args[i], "-n", 3)))
    {
        flag_nl = 1;
        i++;
    }
	while (args[i] != 0)
	{
		ft_putstr_fd(args[i], fd);
        if (args[i + 1] != 0)
            write(fd, " ", 1);
		i++;
	}
    if (flag_nl == 0)
        write(fd, "\n", 1);
    close(0);
    close(1);
}

void	pwd(int *flag)
{
	char	buffer[PATH_MAX + 1];
	char	*path;

    *flag = 1;
	path = getcwd(buffer, sizeof(buffer));
	if (path == NULL)
		ft_printf("Error\n");
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
}

int    add_to_table(t_cmd_args *c_a, t_env **env_table, int i, t_env *env)
{
    char    *name;
    int     len;

    len = 0;
    while(c_a->args[i][len] != '\0' && c_a->args[i][len] != '=')
        len++;
    name = ft_strndup(c_a->args[i], (len + 1));
    if (name == NULL)
    {
        free(env);
        printf("minishell: error allocating memory\n");
        return (-1);
    }
    table_delete(name, env_table);
    if (get_value(env, c_a->args[i], env_table) == -1)
    {
        free(name);
        free(env);
        printf("minishell: error allocating memory\n");
        return (-1);
    }
    return (1);
}

void    export(t_cmd_args *c_a, t_env **env_table, int *flag)
{
    t_env   *env;
    int     len;
    int     i;

    i = -1;
    *flag = 1;
    if (c_a->args[0] == NULL)
        export_env(env_table, flag);
    while(c_a->args[++i] != NULL)
    {
        len = 0;
        env = malloc(sizeof(t_env));
        if (env == NULL)
        {
            printf("minishell: error allocating memory\n");
            return ;
        }
        while(c_a->args[i][len] != '\0' && c_a->args[i][len] != '=')
            len++;
        if (c_a->args[i][len] != '\0')
            if (add_to_table(c_a, env_table, i, env) == -1)
                return ;
    }
}

void    unset(t_cmd_args *c_a, t_env **env_table, int *flag)
{
    int     i;
    char    *name;
    
    i = 0;
    *flag = 1;
    while(c_a->args[i] != NULL)
    {
        name = ft_strjoin(c_a->args[i], "=");
        if (name == NULL)
        {
            printf("minishell: error allocating memory");
            return ;
        }
        table_delete(name, env_table);
        free(name);
        i++;
    }
}
