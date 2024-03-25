/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:12:07 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/22 13:57:05 by vsavolai         ###   ########.fr       */
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

char    *clean_quotes(char *cmd, int cc)
{
    int     i;
    int     j;
    char    quote;
    char    *new_cmd;

    new_cmd = malloc(sizeof(char) * (cc + 1));
    if (new_cmd == 0)
        return (NULL);
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
    free(cmd);
    return (new_cmd);
}

int remove_cmd_quotes(t_cmd_args **cmd_args)
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
        cmd_args[i]->cmd = clean_quotes(cmd_args[i]->cmd, cc);
        if (cmd_args[i]->cmd == NULL)
            return (-1);
        i++;
    }
    return (0);
}

char    *clean_arg(char *arg)
{
    int i;
    int cc;

    i = 0;
    cc = 0;
    while(arg[i] != '\0')
    {
        if (arg[i] == '"' || arg[i] == '\'')
            cc += get_cc(arg, &i, arg[i]);
        else
            cc++;
        if (arg[i] != '\0')
            i++;
    }
    arg = clean_quotes(arg, cc);
    return (arg);
}

int remove_arg_quotes(t_cmd_args **cmd_args)
{
    int i;
    int j;

    i = 0;
    while(cmd_args[i])
    {
        j = 0;
        while(cmd_args[i]->args[j])
        {
            cmd_args[i]->args[j] = clean_arg(cmd_args[i]->args[j]);
            if (cmd_args[i]->args[j] == NULL)
                return (-1);
            j++;
        }
        i++;
    }
    return (0);
}
