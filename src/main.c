/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:35:14 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/23 17:13:23 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int main(int ac, char **ag, char **envp)
{
    int f1;
    int f2;
    // int i = 0;
    
    // get path, use split(:) to get all the possible cmd paths
    // while (envp[i])
    //     printf("[%s]\n", envp[i++]); 
    if (ac == 5)
    {
       f1 = open(ag[1], O_RDONLY);
       f2 = open(ag[4], O_RDONLY);        
       if (!f1 || !f2)
           return (-1);
       pipex(f1, f2, ag, envp);
       if (!close(f1)  || !close(f2))
           return (-1);
    }
    return (0);
}