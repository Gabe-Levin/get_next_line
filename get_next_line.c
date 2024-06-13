/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:29:50 by glevin            #+#    #+#             */
/*   Updated: 2024/06/13 22:47:17 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_istrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != (unsigned char)c)
	{
		if (!str[i++])
			return (-1);
	}
	return (i);
}

void	add_to_stash(char **stash, char *buf)
{
	char	*tmp_stash;

	tmp_stash = ft_strjoin(*stash, buf);
	if (tmp_stash == NULL)
	{
		free(buf);
		free(*stash);
		*stash = NULL;
	}
	else
	{
		free(*stash);
		*stash = tmp_stash;
	}
}

char	*check_new_line(char **stash)
{
	int		eol_loc;
	char	*next_line;
	char	*tmp_stash;

	eol_loc = ft_istrchr(*stash, '\n');
	if (eol_loc >= 0)
	{
		next_line = ft_substr(*stash, 0, eol_loc + 1);
		tmp_stash = ft_strdup(*stash + eol_loc + 1);
		if (tmp_stash == NULL)
		{
			free(*stash);
			return (NULL);
		}
		free(*stash);
		*stash = tmp_stash;
		return (next_line);
	}
	return (NULL);
}

char	*read_file(int fd, char **stash)
{
	char	*buf;
	int		byte_cnt;
	char	*next_line;

	byte_cnt = 1;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	next_line = check_new_line(stash);
	while (!next_line && byte_cnt != 0)
	{
		byte_cnt = read(fd, buf, BUFFER_SIZE);
		buf[byte_cnt] = '\0';
		add_to_stash(stash, buf);
		next_line = check_new_line(stash);
	}
	free(buf);
	if (byte_cnt == 0)
	{
		next_line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*stash;

	if (stash == NULL)
	{
		stash = (char *)malloc(1);
		if (stash == NULL)
			return (NULL);
		stash[0] = '\0';
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	next_line = read_file(fd, &stash);
	if (ft_strlen(next_line) != 0)
		return (next_line);
	free(stash);
	stash = NULL;
	free(next_line);
	return (NULL);
}

// int	main(void)
// {
// 	int fd;
// 	int i;
// 	char *line;

// 	i = 0;

// 	fd = open("test2.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL && i < 20)
// 	{
// 		// printf("fd: %i", fd);
// 		printf("%i: %s", i, line);
// 		free(line);
// 		// printf("TEST RESULT: %s", get_next_line(fd));
// 		i++;
// 	}
// 	return (1);
// }