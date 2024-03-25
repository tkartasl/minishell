/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:45:08 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/25 15:33:52 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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
    /*if ((*cmd_args)->pipe_count == 1)
        check_builtins(cmd_args[0]);
    else*/
        run_commands(cmd_args, (*cmd_args)->pipe_count, env_table);
    free_struct_array(cmd_args);
}
