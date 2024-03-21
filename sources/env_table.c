/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:54:18 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/21 12:00:39 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_get_env(char *name, t_env **env_table)
{
    t_env   *new;
    new = search_table(name, env_table);
    return (new->value);
}

void   init_hash_table(t_env **new)
{
    int i;

    i = 0;
    while(i < TABLE_SIZE)
    {
        new[i] = NULL;
        i++;
    }
}

int hash(char *name)
{
    int len;
    unsigned int hash_value;
    int i;

    len = ft_strlen(name);
    hash_value = 0;
    i = 0;
    while(i < len)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
        i++;
    }
    return (hash_value);
}

int get_value(t_env *env, char *envp, t_env **env_table)
{
    char    *name;
    char    *value;
    int     len_name;
    int     len;

    len_name = 0;
    len = ft_strlen(envp);
    while(envp[len_name] != '=')
        len_name++;
    name = ft_strndup(envp, len_name + 1);
    if (name == NULL)
        return (-1);
    len_name++;
    value = ft_strndup((envp + len_name), len);
    if (value == NULL)
    {
        free(name);
        return (-1);
    }
    env->name = name;
    env->value = value;
    if (table_insert(env, env_table) == -1)
        return(-1);
    return (1);
}

int create_envs(char **envp, t_env **env_table)
{
    int     i;

    i = 0;
    init_hash_table(env_table);
    while(envp[i] != 0)
    {
        env_table[i] = malloc(sizeof(t_env));
        if (env_table[i] == NULL)
        {
            printf("minishell: error allocating memory");
            return (-1);
        }
        if (get_value(env_table[i], envp[i], env_table) == -1)
        {
            printf("minishell: error allocating memory");
            return (-1);
        }
        i++;
    }
    return (1);
}