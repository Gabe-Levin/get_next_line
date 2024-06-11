char	*get_next_line(int fd)
{
	char		*buf;
	char		*current_line;
	static char	*stash;
	int			eol_loc;
	int			byte_cnt;

	printf("==> HERE");
	buf = (char *)malloc(BUFFER_SIZE * sizeof(char));
	printf("==> HERE");
	if (buf == NULL)
		return (NULL);
	if (stash == NULL)
	{
		stash = (char *)malloc(1);
		if (stash == NULL)
		{
			free(buf);
			return (NULL);
		}
		stash[0] = '\0';
		printf("==> HERE");
	}
	else
	{
		printf("==> HERE");
		eol_loc = ft_strchr(stash, '\n');
		if (eol_loc != 0)
		{
			current_line = ft_substr(stash, 0, eol_loc);
			stash += eol_loc + 1;
			return (ft_substr(current_line, 0, eol_loc));
		}
		current_line = ft_strdup(stash);
	}
	while (1)
	{
		printf("==> HERE");
		byte_cnt = read(fd, buf, BUFFER_SIZE);
		eol_loc = ft_strchr(buf, '\n');
		if (byte_cnt == 0)
		{
			stash = ft_strdup(current_line + eol_loc + 1);
			current_line = ft_substr(current_line, 0, eol_loc + 1);
			return (current_line);
		}
		current_line = ft_strjoin(current_line, ft_substr(buf, 0, eol_loc + 1));
		if (byte_cnt < BUFFER_SIZE)
		{
			stash = ft_strdup("");
			return (current_line);
		}
		else if (eol_loc != 0)
		{
			stash = ft_strdup(buf + eol_loc + 1);
			printf("==> stash:%s", stash);
			printf("==> HERE");
			return (current_line);
		}
		current_line = ft_strjoin(current_line, buf);
	}
	free(current_line);
	free(buf);
}