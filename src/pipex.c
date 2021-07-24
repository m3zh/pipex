/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:40:47 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/24 17:28:37 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

static  int    list_elem(char **ag, int f1, int f2, char **ep)
{   
    int pipea[2];
    int pipeb[2];
    int     status;
    pid_t   p1;
    // pid_t   p2;
    char *myag[] = { "-l", NULL };

    (void)ag;
    (void)f2;
    status = 0;
    pipe(pipea);
    pipe(pipeb);
    printf("%d\n", pipea[0]);
    printf("%d\n", pipea[1]);
    p1 = fork();
    if (p1 < 0)
        return (p1); // add errno
    if (!p1)
    {
        printf("child\n");
        dup2(f1, STDOUT_FILENO);
        dup2(pipea[1], f1);
        close(f1);
        close(pipea[0]);
        close(pipea[1]);
        execve("/bin/ls", myag, ep);
        perror("execve");
        return 0;
    }
    else
    // // {
    // //     close(pipefd[1]);
    // //     printf("parent\n");
    // //     dup2(f1, STDIN_FILENO);
    // //     dup2(pipefd[0], f1);
    // //     execve("/bin/ls", myag, ep);
    // //     perror("execve");
    // // }
    // p2 = fork();
    // if (p2 < 0)
    //     return (p2); // add errno
    // if (!p2)
    {
        printf("child2\n");
        // close(pipefd[0]);
        dup2(f2, STDIN_FILENO);
        dup2(pipea[0], f2);
        close(f2);
        close(pipea[0]);
        close(pipea[1]);
        execve("/usr/bin/wc", myag, ep);
        perror("execve");
        return 0;
    }
    // else
    // {
    //     close(pipefd[1]);
    //     dup2(pipefd[0], STDIN_FILENO);
    //     execve(ag[3], ag, ep);
    // }
    close(pipea[0]);
    close(pipea[1]);
    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    return (status);
}

// open("foo.txt", O_WRONLY);
// dup2(oldfd, newfd); it closes the new fd, copies the fd table of the old fd to the new one
// oldfd is f1 and newfd is 1 (the child ?)
//1 is std out >
// 0 is std in

void    pipex(int f1, int f2, char **ag, char **ep)
{
    // char *args[100] = {"/bin/ls", "-l", "file", NULL}

    // execve(args[0], args, NULL);
    // pipefd[0] = f1;
    // pipefd[1] = f2;
    (void)f1;
    if (!ft_strncmp(ag[2], "ls", 2))
        list_elem(ag, f1, f2, ep);
}
