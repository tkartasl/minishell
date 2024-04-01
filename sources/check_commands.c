/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:45:08 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/01 09:41:20 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_table(t_env **table)
{
    int i;

    i = 0;
    while(i < TABLE_SIZE)
    {
        if (table[i] == NULL)
            printf("\t%i\t---\n", i);
        else if (table[i] == DELETED_NODE)
            printf("\t%i\t---<deleted>\n", i);
        else 
            printf("\t%i\t%s%s\n", i, table[i]->name, table[i]->value);
        i++;
    }
}

int check_builtins(t_cmd_args *cmd_args, t_env **env_table)
{
    int flag;

    flag = 0;
    if (ft_strncmp(cmd_args->cmd, "export", 7) == 0)
        export(cmd_args, env_table, &flag);
    else if (ft_strncmp(cmd_args->cmd, "pwd", 4) == 0)
        pwd(&flag);
    else if (ft_strncmp(cmd_args->cmd, "echo", 5) == 0)
        echo(cmd_args->args, 1, &flag);
    else if (ft_strncmp(cmd_args->cmd, "unset", 6) == 0)
        unset(cmd_args, env_table, &flag);
    else if (ft_strncmp(cmd_args->cmd, "env", 4) == 0)
        env(env_table, &flag);
    return (flag);
}

void    check_cmds(t_cmd_args **cmd_args, t_env **env_table)
{
    int flag;

    flag = 0;
    if (get_envs(cmd_args, env_table) == 0)
        flag = -1;
    if (remove_cmd_quotes(cmd_args) == -1)
        flag = -1;
    if (remove_arg_quotes(cmd_args) == -1)
        flag = -1;
    if (remove_file_quotes((*cmd_args)->head_hdocs) == -1)
        flag = -1;
    if (remove_file_quotes((*cmd_args)->head_redir) == -1)
        flag = -1;
    if (flag == -1)
    {
        free_struct_array(cmd_args);
        printf("minishell: error allocating memory\n");
        return ;
    }
    if ((*cmd_args)->pipe_count == 1)
       flag = check_builtins(cmd_args[0], env_table);
    if (flag == 0)
        run_commands(cmd_args, (*cmd_args)->pipe_count, env_table);
    free_struct_array(cmd_args);
}
