/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:35:14 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/30 15:58:05 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int ac, char **ag, char **envp)
{
	int	f1;
	int	f2;

	if (ac != 5)
		return (write(1, "Invalid number of arguments.\n", 29));
	if (access(ag[1], F_OK | R_OK) < 0)
		return (write(2, strerror(errno), ft_strlen(strerror(errno))));
	f1 = open(ag[1], O_RDONLY);
	f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (write(2, strerror(errno), ft_strlen(strerror(errno))));
	pipex(f1, f2, ag, envp);
	if (close(f1) < 0 || close(f2) < 0)
		return (write(2, strerror(errno), ft_strlen(strerror(errno))));
	return (0);
}
