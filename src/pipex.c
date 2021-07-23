/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:40:47 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/23 15:42:35 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static  void    list_elem(char **ag, int f2, int *pipefd, char **ep)
{
    int     status;
    pid_t   cpid;

    status = 0;
    pipe(pipefd);
    cpid = fork();
    if (!cpid)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execve(ag[2], ag, ep);
    }
    else
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        execve(ag[3], ag, ep);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    write(f2, "hello", 5);
}

// open("foo.txt", O_WRONLY);
// dup2(oldfd, newfd); it closes the new fd, copies the fd table of the old fd to the new one
// oldfd is f1 and newfd is 1 (the child ?)
//1 is std out >
// 0 is std in

void    pipex(int f1, int f2, char **ag, char **ep)
{
    int pipefd[2];
    // char *args[100] = {"/bin/ls", "-l", "file", NULL}

    // execve(args[0], args, NULL);
    (void)f1;
    if (!ft_strncmp(ag[2], "ls", 2))
        list_elem(ag, f2, pipefd, ep);
}
/*
pid_t p1, p2;

p1 = fork()
if (p1 < 0)
    Error
if (p1 == 0)
    child execve 1 pipex()
p2 = fork()
if (p2 < 0)
    Error
if (p2 == 0)
    child execve 2 pipex()
else
    parent
    wait(p1)
    wait(p2)
    */