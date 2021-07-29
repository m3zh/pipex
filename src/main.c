/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:35:14 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/29 18:00:48 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int ac, char **ag, char **envp)
{
	int	f1;
	int	f2;

	if (ac != 5)
		return (printf("Invalid number of arguments.\n"));
	if (access(ag[1], F_OK | R_OK) < 0 || access(ag[4], F_OK | W_OK) < 0)
		return (printf("File: %s\n", strerror(errno)));
	f1 = open(ag[1], O_RDONLY);
	f2 = open(ag[4], O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (printf("Open file: %s\n", strerror(errno)));
	pipex(f1, f2, ag, envp);
	if (close(f1) < 0 || close(f2) < 0)
		return (printf("Close file: %s\n", strerror(errno)));
	return (0);
}
