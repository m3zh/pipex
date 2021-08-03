/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:40:47 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/02 15:42:11 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	init_cmd(t_cmd *c, int f)
{
	c->f = f;
	c->path = 0;
	c->cmd = 0;
	c->args[0] = 0;
}

static void	free_all(t_cmd *c, t_cmd *d)
{
	free_struct(c);
	free_struct(d);
}

static char	**get_path(char **ep)
{
	char	**ret;
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
			ret = ft_splitpath(env, ':');
			if (!ret)
			{
				free(env);
				return (NULL);
			}
			free (env);
			return (ret);
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
	t_cmd	cmd1;
	t_cmd	cmd2;

	init_cmd(&cmd1, f1);
	init_cmd(&cmd2, f2);
	if (!get_cmd(envp, &cmd1, ag[2]) || !get_cmd(envp, &cmd2, ag[3]))
		return (free_all(&cmd1, &cmd2));
	if (!check_cmd(&cmd1) || !check_cmd(&cmd2))
		return (free_all(&cmd1, &cmd2));
	exec_cmd(&cmd1, &cmd2, envp);
	free_struct(&cmd1);
	free_struct(&cmd2);
}
