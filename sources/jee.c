#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strndup(const char *s1, int len)
{
	int		n;
	char	*p;

	n = 0;
	p = malloc((len + 1) * sizeof(char));
	if (p == 0)
		return (0);
	while (n < len && s1[n] != 0)
	{
		p[n] = s1[n];
		n++;
	}
	p[n] = 0;
	return (p);
}

char	*ft_skip_whitespace(char *str)
{
	while (*str != 0 && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	return (str);
}

int	get_len(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != ' ' && str[i] != 0 && str[i] != '<' && str[i] != '>')
		i++;
	return (i);	
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != 0 && *s2 != 0)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (haystack == 0 && len == 0)
		return (NULL);
	if (strlen(needle) > strlen(haystack))
		return (NULL);
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] != 0 && i < len)
	{
		if (ft_strcmp(&haystack[i], needle) && (i + strlen(needle)) <= len)
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}

int	get_quotes_len(char *str, char quote)
{
	int		i;

	i = 0;
	i++;
	while (str[i] != 0 && str[i] != quote)
		i++;
	if (str[i] == 0)
		return (0);
	i++;
	return (i);
}

char	*skip_redirs(char *cmd_line)
{
	if (*cmd_line == '>' && (*(cmd_line + 1) == '>'))
		cmd_line = cmd_line + 2;
	if (*cmd_line == '<' && (*(cmd_line + 1) == '<'))
		cmd_line = cmd_line + 2;
	if (*cmd_line == '<' || *cmd_line == '>')
		cmd_line++;
	cmd_line = ft_skip_whitespace(cmd_line);
	return (cmd_line);
}

char *find_cmd(char *cmd_line)
{
	char	*cmd;
	int		len;

	len = 0;
	while (1)
	{
		cmd_line = skip_redirs(cmd_line);
		while(*cmd_line != ' ' && cmd_line != 0)
			cmd_line++;
		cmd_line = ft_skip_whitespace(cmd_line);
		if (*cmd_line != '<' && *cmd_line != '>')
			break ;
	}
	len = get_len(cmd_line);
	cmd = ft_strndup(cmd_line, len);
	if (cmd == 0)
		printf("error\n");
	return	(cmd);	
}

char	*parse_command(char *cmd_line)
{
	int		len;
	char	*cmd;

	len = 0;
	cmd = 0;
	cmd_line = ft_skip_whitespace(cmd_line);
	if (*cmd_line != '<' && *cmd_line != '>')
	{
		cmd_line = ft_skip_whitespace(cmd_line);
		if (*cmd_line == '\'' || *cmd_line == '\"')
			len = get_quotes_len(cmd_line, *cmd_line);
		if (len == 0)
			len = get_len(cmd_line);
		printf("%s\n", cmd_line);
		printf("JEEEE%d\n", len);
		cmd = ft_strndup(cmd_line, len);
		if (cmd == 0)
			return (0);
		return (cmd);
	}
	else
		cmd = find_cmd(cmd_line);
	return (cmd);	
}

void	get_arg_count(char *cmd_line, int *count)
{
	while (*cmd_line != 0)
	{
		if (*cmd_line != '<' && *cmd_line != '>' && *cmd_line != 0)
		{
			*count += 1;
			while (*cmd_line != ' ' && *cmd_line != 0)
				cmd_line++;
			cmd_line = ft_skip_whitespace(cmd_line);
		}
		else
		{
			while (*cmd_line != 0 && (*cmd_line == '>' || *cmd_line == '<'))
			{
				//printf("%c\n", *cmd_line);
				if ((*cmd_line == '<' || *cmd_line == '>') && (*(cmd_line + 1) == '<' || *(cmd_line + 1) == '>'))
					cmd_line = cmd_line + 2;
				if (*cmd_line == '<' || *cmd_line == '>')
					cmd_line++;
				cmd_line = ft_skip_whitespace(cmd_line);
				while (*cmd_line != 0 && *cmd_line != ' ')
					cmd_line++;
				cmd_line = ft_skip_whitespace(cmd_line);
			}
		}
	}
}

char	*get_args(char *cmd_line)
{
	while (*cmd_line != 0)
	{
		while(*cmd_line != ' ' && *cmd_line != 0 && *cmd_line != '<' && *cmd_line != '>')
			cmd_line++;
		cmd_line = ft_skip_whitespace(cmd_line);
		if (*cmd_line != '<' && *cmd_line != '>')
			return (cmd_line);
		else
		{
			cmd_line = skip_redirs(cmd_line);
			while (*cmd_line != 0 && *cmd_line != ' ')
				cmd_line++;
			cmd_line = ft_skip_whitespace(cmd_line);
			if (*cmd_line != '<' && *cmd_line != '>')
				return (cmd_line);
			cmd_line = skip_redirs(cmd_line);
		}
	}
	return (0);
}

char	**parse_arguments(char *line, char *line2)
{
	char	**args;
	int		i;
	int		count;
	int		len;

	count = 0;
	len = 0;
	i = 0;
	get_arg_count(line, &count);
	printf("%d\n", count);
	args = malloc((count + 1) * sizeof(char *));
	if (args == 0)
		printf("Error");
	while (i < count)
	{
		line2 = get_args(line2);
		len = get_len(line2);
		args[i] = ft_strndup(line2, len);
		if (args[i] == 0)
			printf("Error");
		i++;
	}
	args[i] = 0;
	return (args);
}

int main()
{
	char *test;
	char testi1[]= " \" <file ";
	//char testi[]= "cat!!! sana3>file >file <file sana 4 >file >>file sana1 < moi > jee sana2";
	int i;

	i = 0;
	test = parse_command(testi1);
	printf("%s\n", test);
}