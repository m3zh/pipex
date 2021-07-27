/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:35:14 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/27 15:21:42 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int main(int ac, char **ag, char **envp)
{
    int f1;
    int f2;

    if (ac == 5)
    {
        f1 = open(ag[1], O_CREAT | O_RDONLY);
        f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);     
        if (f1 < 0 || f2 < 0)
           return (printf("Error: %s\n", strerror(errno)));
        pipex(f1, f2, ag, envp);
        if (close(f1) < 0 || close(f2) < 0)
           return (printf("Error: %s\n", strerror(errno)));
        system("leaks pipex");
    }
    return (0);
}