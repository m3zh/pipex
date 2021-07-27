/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:34:21 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/27 15:20:21 by mlazzare         ###   ########.fr       */
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

int         pipex(int f1, int f2, char **ag, char **ep);

/*
* STRING UTILS
*/

char		**ft_split(char const *s, char c);
size_t      ft_strlen(const char *str);
int	        ft_strncmp(const char *s1, const char *s2, size_t n);
char	    *ft_substr(const char *s, unsigned int start, size_t len);

#endif