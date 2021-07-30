/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:40:47 by mlazzare          #+#    #+#             */
/*   Updated: 2021/07/29 17:56:53 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static int	free_arr(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	return (0);
}

static void	free_struct(t_cmd *c)
{
	free(c->cmd);
	free_arr(c->path);
	free_arr(c->args);
}

static char	**get_path(char **ep)
{
	char	*env;
	int		i;

	i = -1;
	while (ep[++i])
	{
		if (!ft_strncmp(ep[i], "PATH=", PATH))
		{
			env = ft_substr(ep[i], START, ft_strlen(ep[i]));
			if (!env)
				return (NULL);
			return (ft_splitpath(env, ':'));
		}
	}
	return (NULL);
}

static int	get_cmd(char **ep, t_cmd *c, char *cmd)
{
	int		i;
	char	**tmp;

	i = -1;
	c->path = get_path(ep);
	if (!c->path)
		return (0);
	tmp = ft_splitpath(cmd, ' ');
	if (!tmp)
		return (0);
	c->cmd = ft_substr(tmp[i + 1], 0, ft_strlen(tmp[i + 1]) - 1);
	if (!c->cmd)
		return (free_arr(tmp));
	while (tmp[++i])
	{
		c->args[i] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]) - 1);
		if (!c->args[i])
		{
			free_arr(c->args);
			return (free_arr(tmp));
		}
	}
	c->args[i] = 0;
	free_arr(tmp);
	return (1);
}

void	pipex(int f1, int f2, char **ag, char **envp)
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	cmd1 = malloc(sizeof(t_cmd));
	cmd2 = malloc(sizeof(t_cmd));
	cmd1->f = f1;
	cmd2->f = f2;
	if (!get_cmd(envp, cmd1, ag[2])
		|| !get_cmd(envp, cmd2, ag[3]))
	{
		free_struct(cmd1);
		free_struct(cmd2);
		return ;
	}
	exec_cmd(cmd1, cmd2, envp);
	free_struct(cmd1);
	free_struct(cmd2);
}
