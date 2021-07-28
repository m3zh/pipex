/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:34:21 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/28 16:35:37 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# define PATH 5
# define START 6

typedef struct s_cmd 
{
    char *cmd;
    char **path;
    char *args[100];
}   t_cmd;

void        pipex(int f1, int f2, char **ag, char **ep);
void        exec_cmd(int f1, int f2, t_cmd *cmd1, t_cmd *cmd2, char **envp);

/*
* STRING UTILS
*/

char		**ft_split(char const *s, char c);
size_t      ft_strlen(const char *str);
int	        ft_strncmp(const char *s1, const char *s2, size_t n);
char	    *ft_substr(const char *s, unsigned int start, size_t len);
char        *ft_strdup(const char *src);
char	    *ft_join(char *dst, const char *src);

#endif