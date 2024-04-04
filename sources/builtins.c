/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:05 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/04 11:30:01 by vsavolai         ###   ########.fr       */
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

void    check_ex_args(t_cmd_args *c_a, t_env **env_table, int *flag)
{
    if (c_a->args[0] == NULL)
        export_env(env_table, flag);
}

void    export(t_cmd_args *c_a, t_env **env_table, int *flag)
{
    t_env   *env;
    int     len;
    int     i;

    i = -1;
    *flag = -1;
    check_ex_args(c_a, env_table, flag);
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
        table_delete(c_a->args[i], env_table);
        printf("%s\n", c_a->args[i]);
        if (c_a->args[i][len] != '\0')
            if (get_value(env, c_a->args[i], env_table) == -1)
            {
                printf("minishell: error allocating memory\n");
                return ;
            }
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
