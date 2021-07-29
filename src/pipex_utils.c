/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:02 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/29 16:41:53 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void child_process(int f1, int *pipefd, t_cmd *c, char **envp)
{
    int     i;
    char    *cmd;

    i = -1;
    dup2(f1, STDIN_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[0]);
    while (c->path[++i])
    {
        cmd = ft_join(c->path[i], c->cmd);
        if (!cmd)
            return ;
        execve(cmd, c->args, envp);
        free(cmd);
    }
    exit(EXIT_SUCCESS);
}

static void parent_process(int f2, int *pipefd, t_cmd *c, char **envp) 
{
    int     i;
    int     status;
    char    *cmd;

    i = -1;
    status = 0;
    waitpid(-1, &status, 0);
    dup2(f2, STDOUT_FILENO);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[1]);
    while (c->path[++i])
    {
        cmd = ft_join(c->path[i], c->cmd); // for tutorial say you are in a pipe if you print, it will be printed on stdout which is your file
        if (!cmd)
            return ;
        execve(cmd, c->args, envp);
        free(cmd);
    }  
    exit(EXIT_SUCCESS);
}

void    exec_cmd(int f1, int f2, t_cmd *cmd1, t_cmd *cmd2, char **envp)
{   
    int     pipefd[2];
    int     i;
    pid_t   p1;

    i = -1;
    pipe(pipefd);
    p1 = fork();
    if (p1 < 0)
        return (perror("Fork"));
    if (!p1)
        child_process(f1, pipefd, cmd1, envp);
    else
        parent_process(f2, pipefd, cmd2, envp);
}