/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:40:47 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/28 16:43:34 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void free_arr(char **path)
{
	int i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

static void free_struct(t_cmd *c)
{
    free(c->cmd);
    free_arr(c->path);
    free_arr(c->args);
}

static void  free_all(t_cmd *c1, t_cmd *c2)
{
    free_struct(c1);
    free_struct(c2);
}

static char **get_path(char **ep)
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
            return (ft_split(env, ':'));
        }
    }
    return (NULL);
}

static  int get_cmd(char **ep, t_cmd *c, char *cmd)
{
    int     i;
    char    **tmp;

    i = 0;
    c->path = get_path(ep);
    if (!c->path)
        return (0);
    tmp = ft_split(cmd, ' ');
    if (!tmp)
        return (0);
    c->cmd = ft_strdup(tmp[i]);
    while (tmp[++i])
        c->args[i - 1] = ft_strdup(tmp[i]);
    c->args[i - 1] = 0;
    free_arr(tmp);
    return (1);
}

void    pipex(int f1, int f2, char **ag, char **envp)
{
    int i;
    t_cmd   *cmd1;
    t_cmd   *cmd2;

    i = -1;
    cmd1 = malloc(sizeof(t_cmd));
    cmd2 = malloc(sizeof(t_cmd));
    if (!get_cmd(envp, cmd1, ag[2])
        || !get_cmd(envp, cmd2, ag[3]))
        return (free_all(cmd1, cmd2));
    exec_cmd(f1, f2, cmd1, cmd2, envp);
    free_struct(cmd1);
    free_struct(cmd2);
}