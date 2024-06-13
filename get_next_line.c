/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:29:50 by glevin            #+#    #+#             */
/*   Updated: 2024/06/13 21:45:18 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
	{
		size++;
	}
	return (size);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *string)
{
	char	*str2;
	size_t	string_len;

	string_len = ft_strlen(string) + 1;
	str2 = malloc(string_len * sizeof(char));
	if (str2 == NULL)
		return (NULL);
	return ((char *)ft_memcpy(str2, string, string_len));
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	s_len;
	size_t			i;

	s_len = ft_strlen(s);
	if (s_len < start)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	s3 = ft_memcpy(s3, s1, s1_len + 1);
	while (s2[i])
	{
		s3[s1_len + i] = s2[i];
		i++;
	}
	s3[s1_len + i] = '\0';
	return (s3);
}
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

char	*add_to_stash(char *stash, char *buf)
{
	char	*tmp_stash;

	tmp_stash = ft_strjoin(stash, buf);
	if (tmp_stash == NULL)
	{
		free(buf);
		free(stash);
		return (NULL);
	}
	free(stash);
	return (tmp_stash);
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
		*stash = add_to_stash(*stash, buf);
		if (*stash == NULL)
		{
			free(buf);
			free(*stash);
			return (NULL);
		}
		next_line = check_new_line(stash);
	}
	free(buf);
	if (byte_cnt == 0)
	{
		next_line = ft_strdup(*stash);
		*stash = NULL;
		free(*stash);
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