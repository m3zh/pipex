/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:40:47 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/27 15:21:02 by mlazzare         ###   ########.fr       */
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
if (p2 == 0
    child execve 2 pipex()
else
    parent
    wait(p1)
    wait(p2)
    */

static  int    list_elem(char **ag, int f1, int f2, char **ep)
{   
    int     pipefd[2];
    int     status;
    pid_t   p1;
    // pid_t   p2;
    char *myag[] = { "-l", NULL };
    // char buff[100];

    (void)ag;
    (void)f2;
    status = 0;
    pipe(pipefd);
    printf("%d\n", f1);
    printf("%d\n", f2);
    printf("%d\n", pipefd[0]);
    printf("%d\n", pipefd[1]);
    p1 = fork();
    if (p1 < 0)
        return (p1); // add errno
    if (!p1)
    {
        printf("child\n");
        dup2(f1, STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(f1);
        execve("/bin/ls", myag, ep);
        perror("execve");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("parent\n");
        dup2(f2, STDOUT_FILENO);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        execve("/usr/bin/wc", myag, ep);
        perror("execve");
        exit(EXIT_SUCCESS);
    }
    // p2 = fork();
    // if (p2 < 0)
    //     return (p2); // add errno
    // if (!p2)
    // {
    //     close(pipefd[1]);
    //     printf("parent\n");
    //     dup2(f2, STDIN_FILENO);
    //     dup2(pipefd[0], f2);
    //     close(pipefd[0]);
    //     close(pipefd[1]);
    //     execve("/usr/bin/wc", myag, ep);
    //     perror("execve");
    //     exit(EXIT_SUCCESS);
    // }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    // int size;
    // while ((size = read(pipefd[0], buff, sizeof(buff))) > 0) {
    //      write(pipefd[0], buff, size);
    // }
    return (status);
}

static void free_path(char **path)
{
	int i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

/*
* ep = env params;
*/

static char **get_path(char **path, char **ep)
{
    char *env;
    int i;

    i = -1;
    while (ep[++i])
    {
        if (!ft_strncmp(ep[i], "PATH=", 5))
        {
            env = ft_substr(ep[i], 6, ft_strlen(ep[i]));
            if (!env)
                return (NULL);
            path = ft_split(env, ':');       
            return (path);
        }
    }
    return (NULL);
}

int    pipex(int f1, int f2, char **ag, char **ep)
{
    char **path;

    path = NULL;
    path = get_path(path, ep);
    if (!path)
        return (printf("Error: %s\n", strerror(errno)));
    if (!ft_strncmp(ag[2], "ls", 2))
        list_elem(ag, f1, f2, path);
    free_path(path);
    return (1);
}
