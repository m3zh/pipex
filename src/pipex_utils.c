/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:02 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/27 16:55:13 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void child_process(int *pipefd, char **opts, char **envp)
{
    dup2(f1, STDIN_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[0]);
    execve("/bin/ls", myag, envp);
    perror("execve");
    exit(EXIT_SUCCESS);
}

static void parent_process(int *pipefd, int status, char **opts, char **envp)
{
    waitpid(-1, &status, 0);
    dup2(f2, STDOUT_FILENO);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[1]);
    execve("/usr/bin/wc", myag, envp);
    perror("execve");
    exit(EXIT_SUCCESS);
}

int    exec_cmd(int f1, int f2, char *cmd1, char *cmd2, char **envp)
{   
    int     pipefd[2];
    int     status;
    pid_t   p1;

    status = 0;
    pipe(pipefd);
    p1 = fork();
    if (p1 < 0)
        return (printf("Error: %s\n", strerror(errno)));
    if (!p1)
        child_process(pipefd, opts, envp);
    else
        parent_process(pipefd, status, opts, envp);
    return (status);
}