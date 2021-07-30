/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:02 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/29 17:59:31 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	child_process(int *pipefd, t_cmd *c, char **envp)
{
	int		i;
	char	*cmd;

	i = -1;
	dup2(c->f, STDIN_FILENO);
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

static void	parent_process(int *pipefd, t_cmd *c, char **envp)
{
	int		i;
	int		status;
	char	*cmd;

	i = -1;
	status = 0;
	waitpid(-1, &status, 0);
	dup2(c->f, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
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

void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	int		pipefd[2];
	pid_t	p1;

	pipe(pipefd);
	p1 = fork();
	if (p1 < 0)
		return (perror("Fork"));
	if (!p1)
		child_process(pipefd, cmd1, envp);
	else
		parent_process(pipefd, cmd2, envp);
}
