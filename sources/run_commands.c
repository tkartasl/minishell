/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:25:50 by vsavolai          #+#    #+#             */
/*   Updated: 2024/03/07 10:55:41 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char check_unclosed_quotes(char *cmd)
{
    char    *temp;
    int     quotes;
    char    quote;
    int     quote_found;

    quotes = 0;
    quote_found = 0;
    temp = cmd;
    while(*temp)
    {
        if (quote_found == 0 && (*temp == '\'' || *temp == '"'))
        {
            quote = *temp;
            quotes++;
            quote_found = 1;
        }
        temp++;
        if (quote_found == 1 && *temp == quote)
            quotes++;
    }
    if ((quotes % 2) != 0)
        return (0);
    return (quote);
}

void    find_cmd(char *cmd, char **new, char quote)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(cmd[i])
    {
        if (cmd[i] != quote)
        {
            cmd[i] = new[j];
            j++;
        }
        i++;
    }
    new[i] = '\0';
}

char    *remove_quotes(char *cmd, char quote)
{
    int     i;
    int     len;
    char    *new;

    i = 0;
    len = 0;
    while(cmd[i])
    {
        if (cmd[i] != quote)
            len++;
        i++;
    }
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL)
        return (NULL);
    find_cmd(cmd, &new, quote);
    return (new);
}

void    run_builtins(t_cmd_args **cmd_args, char **envp)
{
    char *cmd;
    char quote;

    quote = check_unclosed_quotes(cmd_args[0]->cmd);
    if (quote == 0)
        return (printf("minishell: syntax error unclosed quotes"));
    cmd = remove_quotes(cmd_args[0]->cmd, quote);

}*/

void    run_commands(t_cmd_args **cmd_args, int pipe_count, char **envp)
{
    /*if (pipe_count <= 1)
        run_builtins(cmd_args, envp);
    else*/
        run_pipes(cmd_args, pipe_count, envp);
}