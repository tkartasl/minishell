/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:45:08 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/01 15:53:39 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    run_commands(cmd_args, (*cmd_args)->pipe_count, env_table);
    free_struct_array(cmd_args);
}
