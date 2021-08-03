/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 13:36:41 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/02 15:26:09 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	**freetab(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	return (0);
}

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	if (!s || !s[0])
		return (0);
	i = -1;
	count = 0;
	while (s[++i])
		if ((s[i] != c && s[i + 1] == c)
			|| (s[i] != c && s[i + 1] == '\0'))
			count++;
	return (count);
}

static int	words_len(const char *s, char c, int i)
{
	int	l;

	l = 0;
	while (s && s[i] && s[i] == c)
		i++;
	while (s && s[i] && s[i++] != c)
		l++;
	return (l);
}

static char	**fill_arr(int words, const char *s, char c, char **arr)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (k < words)
	{
		j = 0;
		arr[k] = (char *)malloc(sizeof(char) * (words_len(s, c, i) + 2));
		if (!arr[k])
			return (freetab(arr));
		while (s && s[i] && s[i] == c)
			i++;
		while (s && s[i] && s[i] != c)
			arr[k][j++] = s[i++];
		arr[k][j++] = '/';
		arr[k][j] = '\0';
		k++;
	}
	arr[k] = 0;
	return (arr);
}

char	**ft_splitpath(char *s, char c)
{
	char	**arr;
	int		words;

	if (!s || !s[0])
		return (NULL);
	words = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr = fill_arr(words, s, c, arr);
	return (arr);
}
