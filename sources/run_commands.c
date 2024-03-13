/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:25:50 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/13 14:34:46 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_cc(char *line, int *j, char quote)
{
    int cc;

    cc = 0;
    *j += 1;
    while (line[*j] != quote && line[*j] != 0)
    {
     cc++;
     *j += 1;
    }
    return (cc);
}

int    clean_quotes(char *cmd, int cc, t_cmd_args *cmd_args)
{
    int     i;
    int     j;
    char    quote;
    char    *new_cmd;

    new_cmd = malloc(sizeof(char) * (cc + 1));
    if (new_cmd == 0)
        return (-1);
    i = 0;
    j = 0;
    while(cmd[i] != 0)
    {
        if (cmd[i] == '\'' || cmd[i] == '"')
        {
            quote = cmd[i];
            while(cmd[++i] != quote)
                new_cmd[j++] = cmd[i];
        }
        else
             new_cmd[j++] = cmd[i];
        i++;
    }
    new_cmd[cc] = '\0';
    free(cmd_args->cmd);
    cmd_args->cmd = new_cmd;
    return (0);
}

int    remove_cmd_quotes(t_cmd_args **cmd_args)
{
    int     i;
    int     j;
    int     cc;

    i = 0;
    while(cmd_args[i])
    {
        j = 0;
        cc = 0;
        while (cmd_args[i]->cmd[j] != 0)
        {
            if (cmd_args[i]->cmd[j] == '"' || cmd_args[i]->cmd[j] == '\'')
                cc += get_cc(cmd_args[i]->cmd, &j, cmd_args[i]->cmd[j]);
            else
                cc++;
            if (cmd_args[i]->cmd[j] != 0)
                j++;
        }
        if (clean_quotes(cmd_args[i]->cmd, cc, cmd_args[i]) == -1)
            return (-1);
        i++;
    }
    return (0);
}

void    run_commands(t_cmd_args **cmd_args, int pipe_count, char **envp)
{
    if (remove_cmd_quotes(cmd_args) == -1)
    {
        printf("minishell: malloc fail");
        return ;
    }
    printf("removed quotes: %s\n", cmd_args[0]->cmd);
    /*if (pipe_count <= 1)
        run_builtins(cmd_args, envp);
    else*/
        run_pipes(cmd_args, pipe_count, envp);
        free_struct_array(cmd_args);
}