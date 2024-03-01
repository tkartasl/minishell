/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:38:23 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/01 14:08:09 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NAME_MAX 255
# define PATH_MAX 1024
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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

void		parse_line(char	*line);
char		*find_redir(char *str);
int			get_len(char *str);
char		*find_limiter(char *str);
int			build_list(t_redir **head, char *lim, int index);
t_cmd_args	**get_array(t_redir **redir, t_redir **hdoc, char **line, int pipe);
char		**parse_arguments(char *line, char *line2);
char		*skip_redirs(char *cmd_line);
void		syntax_error(char **cmd_line);
int			check_syntax(char **cmd_lines, int pipe_count);
void		list_build_error(t_redir **hdoc, t_redir **redir, char **cmd_line);
void		redir_lstclear(t_redir **lst, void (*del)(void *));
void		free_struct_array(t_cmd_args **arr);
int			get_pipe_count(char **cmd_lines);

#endif