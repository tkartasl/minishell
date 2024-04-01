/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:53:05 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/28 16:02:26 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args, int fd, int *flag)
{
	int	i;	
	int	j;
	
    *flag = 1;
	i = 0;
	j = 0;
	while (args[i] != 0)
	{
		ft_putstr_fd(args[i], fd);
        if (args[i + 1] != 0)
            write(fd, " ", 1);
		i++;
	}
    write(fd, "\n", 1);
}
/*
void	cd(char	*path)
{
	if (chdir(path) < 0);
		//error
}
*/

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

void export(t_cmd_args *c_a, t_env **env_table, int *flag)
{
    t_env   *env;
    int     len;
    int     i;

    i = 0;
    *flag = 1;
    while(c_a->args[i] != NULL)
    {
        len = 0;
        env = malloc(sizeof(t_env));
        if (env == NULL)
        {
            printf("minishell: error allocating memory");
            return ;
        }
        while(c_a->args[i][len] != '\0' && c_a->args[i][len] != '=')
            len++;
        if (c_a->args[i][len] != '\0')
            if (get_value(env, c_a->args[i], env_table) == -1)
            {
                printf("minishell: error allocating memory");
                return ;
            }
        i++;
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
        printf("nd: %s\n", name);
        table_delete(name, env_table);
        free(name);
        i++;
    }
}

void    env(t_env **env_table, int *flag)
{
    int i;

    i = 0;
    *flag = 1;
    while(i < TABLE_SIZE)
    {
        if (env_table[i] != NULL && env_table[i] != DELETED_NODE)
            printf("%s%s\n", env_table[i]->name, env_table[i]->value);
        i++;
    }
}
