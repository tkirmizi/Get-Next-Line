/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:05:49 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/06/17 00:06:44 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_filler(int fd, char *remind, char *buffer);
static char	*set_line(char **line);
static char	*ft_strchr(const char *s, int c);

// void leaks(void)
// {
// 	system("leaks a.out");
// }

char	*get_next_line(int fd)
{

	static char	*previous;
	char		*final_line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	final_line = line_filler(fd, previous, buffer);
	free(buffer);
	if (!final_line)
		return (NULL);
	previous = set_line(&final_line);
	return (final_line);
}
static char	*line_filler(int fd, char *previous, char *buffer)
{
	ssize_t	readed;
	char	*tmp;

	while ((readed = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[readed] = '\0';
		if (!previous)
			previous = ft_strdup("");
		tmp = previous;
		previous = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (readed == -1)
	{
		free(previous);
		return (NULL);
	}
	return (previous);
}


static char *set_line(char **final_line)
{
	char	*right;
	char	*left;
	char	*temp;
	ssize_t	i;
	
	i = 0;
	temp = *final_line;
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	if (temp[i] == 0)
		return (NULL);
	left = ft_substr(temp, 0, i + 1);
	right = ft_substr(temp + i + 1, 0, ft_strlen((temp + i + 1)));
	if (*right == 0)
	{
		free(right);
		right = NULL;
	}
	free(temp);
	*final_line = left;
	return (right);
}
static char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			d;

	i = 0;
	d = c;
	while (s[i])
	{
		if (s[i] == d)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == d)
		return ((char *) &s[i]);
	return (NULL);
}
