/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:45:08 by vsavolai          #+#    #+#             */
/*   Updated: 2024/04/11 12:12:01 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_echo_redirs(t_cmd_args *cmd_args)
{
    int fd1;
    int fd2;
    int flag;

    flag = 0;
    fd1 = 0;
    fd2 = 0;
    if (check_in_redir(cmd_args->head_redir, 0, fd1) == -1)
        return (-1);
    if (check_out_redir(cmd_args->head_redir, 0, fd2, &flag) == -1)
        return (-1);
    return (1);
}

int check_builtins(t_cmd_args *cmd_args, t_env **env_table, int call)
{
    int flag;
   
    flag = 0;
    if (call == 0 && ft_strncmp(cmd_args->cmd, "echo", 5) == 0)
        if (check_echo_redirs(cmd_args) == -1)
            return (-1);
    if (cmd_args->cmd_count == 0 && cmd_args->head_redir != NULL)
    {
        flag = 1;
        check_echo_redirs(cmd_args);
    }
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
    else if (ft_strncmp(cmd_args->cmd, "cd", 3) == 0)
        cd(cmd_args, env_table, &flag);
    return (flag);
}

int check_cmd_syntax(t_cmd_args **cmd_args, t_env **env_table)
{
    (void)env_table;
    if (get_envs(cmd_args, env_table) == 0)
        return (-1);
    if (remove_cmd_quotes(cmd_args) == -1)
        return (-1);
    if (remove_arg_quotes(cmd_args) == -1)
        return (-1);
    if (remove_file_quotes((*cmd_args)->head_hdocs) == -1)
        return (-1);
    if (remove_file_quotes((*cmd_args)->head_redir) == -1)
        return (-1);
    return (0);
}

void    check_cmds(t_cmd_args **cmd_args, t_env **env_table)
{
    int flag;
    int fd1;
    int fd2;

    fd1 = dup(0);
    fd2 = dup(1);
    flag = check_cmd_syntax(cmd_args, env_table);
    if (flag == -1)
    {
        free_struct_array(cmd_args);
        printf("minishell: error allocating memory\n");
        return ;
    }
    if ((*cmd_args)->pipe_count == 1)
    {
       /*if (ft_strncmp(cmd_args[0]->cmd, "exit", 5) == 0)
            ft_exit(env_table, cmd_args);*/
        flag = check_builtins(cmd_args[0], env_table, 0);
    }
    dup2(fd1, 0);
    dup2(fd2, 1);
    if (flag == 0)
        run_commands(cmd_args, (*cmd_args)->pipe_count, env_table);
    free_struct_array(cmd_args);
}
