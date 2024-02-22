/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:38:23 by tkartasl          #+#    #+#             */
/*   Updated: 2024/02/22 12:36:03 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NAME_MAX 255
# define PATH_MAX 1024
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>

typedef struct s_redir
{
	char			arrow;
	char			*filename;
	int				index;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd_args
{
	t_redir		**head_redir;
	t_redir		**head_hdocs;
	char		*cmd;
	char		**args;
	int			pipe_count;
}				t_cmd_args;

#endif