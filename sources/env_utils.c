/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:24:07 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/15 10:03:19 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	table_insert(t_env *env, t_env **env_tabl)
{
	int	index;
	int	i;
	int	try;

	i = 0;
	index = hash(env->name);
	while (i < TABLE_SIZE)
	{
		try = (i + index) % TABLE_SIZE;
		if (env_tabl[try] == NULL || env_tabl[try] == (t_env *)(DELETED_NODE))
		{
			env_tabl[try] = env;
			return (1);
		}
		i++;
	}
	ft_putendl_fd("minishell: env table is full", 2);
	return (-1);
}

t_env	*search_table(char *name, t_env **env_t)
{
	int	index;
	int	try;
	int	i;
	int	len;

	i = 0;
	index = hash(name);
	len = ft_strlen(name);
	while (i < TABLE_SIZE)
	{
		try = (i + index) % TABLE_SIZE;
		if (env_t[try] == (t_env *)(DELETED_NODE))
		{
			i++;
			continue ;
		}
		if (env_t[try] != NULL && ft_strncmp(env_t[try]->name, name, len) == 0
			&& env_t[try]->name[len] == '=')
			return (env_t[try]);
		i++;
	}
	return (NULL);
}

int	table_delete(char *name, t_env **et)
{
	int	index;
	int	i;
	int	try;

	i = 0;
	index = hash(name);
	while (i < TABLE_SIZE)
	{
		try = (i + index) % TABLE_SIZE;
		if (et[try] == (t_env *)(DELETED_NODE))
		{
			i++;
			continue ;
		}
		if (et[try] != NULL && ft_strncmp(et[try]->name, name, 1000) == 0)
		{
			free(et[try]->name);
			free(et[try]->value);
			et[try] = (t_env *)(DELETED_NODE);
			return (1);
		}
		i++;
	}
	return (-1);
}

char	**fill_envp_list(t_env **env_table, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		if (env_table[i] != NULL && env_table[i] != (t_env *)(DELETED_NODE))
		{
			envp[j] = ft_strjoin(env_table[i]->name, env_table[i]->value);
			if (envp[j] == NULL)
			{
				ft_free_pointer_array(envp);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	envp[j] = NULL;
	return (envp);
}

char	**get_env_list(t_env **env_tabl)
{
	char	**envp;
	int		i;
	int		envp_len;

	i = 0;
	envp_len = 0;
	while (i < TABLE_SIZE)
	{
		if ((env_tabl[i] != NULL) && (env_tabl[i] != (t_env *)(DELETED_NODE)))
			envp_len++;
		i++;
	}
	envp = malloc(sizeof(char *) * (envp_len + 1));
	if (envp == NULL)
		return (NULL);
	envp = fill_envp_list(env_tabl, envp);
	if (envp == NULL)
		return (NULL);
	return (envp);
}
