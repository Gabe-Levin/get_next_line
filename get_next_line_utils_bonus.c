/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glevin <glevin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:29:54 by glevin            #+#    #+#             */
/*   Updated: 2024/06/14 21:36:52 by glevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_strdup(const char *string)
{
	char	*str2;
	size_t	string_len;
	size_t	i;

	string_len = ft_strlen(string) + 1;
	str2 = malloc(string_len * sizeof(char));
	if (str2 == NULL)
		return (NULL);
	i = 0;
	while (i < string_len)
	{
		str2[i] = string[i];
		i++;
	}
	return (str2);
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
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		s3[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		s3[s1_len + i] = s2[i];
		i++;
	}
	s3[s1_len + i] = '\0';
	return (s3);
}
