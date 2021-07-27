/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:40:47 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/27 16:50:13 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char **get_path(char **path, char **ep)
{
    char *env;
    int i;

    i = -1;
    while (ep[++i])
    {
        if (!ft_strncmp(ep[i], "PATH=", PATH))
        {
            env = ft_substr(ep[i], START, ft_strlen(ep[i]));
            if (!env)
                return (NULL);
            path = ft_split(env, ':');       
            return (path);
        }
    }
    return (NULL);
}

static void free_path(char **path)
{
	int i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

static  char    **get_cmd(char **path, char **cmd)
{   
    int i;
    char *ret[100];

    i = -1;
    while (path[++i])
    {
        ret[i] =        
    }
    ret[i] = 0;
    return (ret);
}

int    pipex(int f1, int f2, char **ag, char **ep)
{
    char    **path;
    char    **cmd1;
    char    **cmd2;

    path = NULL;
    path = get_path(path, ep);
    if (!path)
        return (printf("Error: %s\n", strerror(errno)));
    cmd1 = get_cmd(path, ag[2]);
    cmd2 = get_cmd(path, ag[3]);
    if (!cmd1 || !cmd2)
        return (printf("Error: %s\n", strerror(errno)));
    exec_cmd(f1, f2, ag[2], ag[3], ep);
    free_path(path);
    return (1);
}