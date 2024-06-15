/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:29:50 by glevin            #+#    #+#             */
/*   Updated: 2024/06/15 16:26:29 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#ifndef MAX_FD
# define MAX_FD 1024
#endif

/*
This function adds the new buffer from the latest read to the end of the stash.
*/
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

/*
This one checks the stash for a new line character. If end of line location
(eol_loc) is not negative, extract that new line and create a new stack
with this line removed.
*/
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

/*
This one reads the file and saves them to buf. BUFFER_SIZE determines how
many bytes are read from the file on a given call. This function will
continue reading the file in BUFFER_SIZE size chunks, as the end of the
file hasn't been reached (byte_cnt ==0) and there is no new line character
in stash. If the end of the file is reached AND there is no new line in
stash, return stash and free it.
*/
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

/*
This one is initializing the static char *stash, in order to have access to
this pointer across multiple function calls. We are checking if the file
descriptior (FD) and BUFFER_SIZE are valid, or if the file is corrupted.
If all looks kosher, we start reading the file into buffer and begin
looking for new lines.

BONUS: This approach initializes stash as an array of char
pointers of length 1024 (an arbitrarily high number for fd). This allows
the function to handle multiple fd's at once. The pointer to the stash
corresponding to a given fd, is stored in the 'fd' index of stash.
Given an fd, the stash[fd] is passed to read_file.

A more storage efficient approach, would be to use a linked list.
This would allow us to store only the minimum required amount of
space for handling multiple fds, as appose to immediately initalizing
a large array of pointers.
*/
char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*stash[1024];

	if (stash[fd] == NULL)
	{
		stash[fd] = (char *)malloc(1);
		if (stash[fd] == NULL)
			return (NULL);
		stash[fd][0] = '\0';
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || 1024 <= fd || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	next_line = read_file(fd, &stash[fd]);
	if (ft_strlen(next_line) != 0)
		return (next_line);
	free(stash[fd]);
	stash[fd] = NULL;
	free(next_line);
	return (NULL);
}
