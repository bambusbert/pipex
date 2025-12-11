/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:21:16 by slambert          #+#    #+#             */
/*   Updated: 2025/10/23 17:21:16 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strjoin_and_free(char **read_buffer, char **stash);
static char	*return_handler(char **stash);
static char	*free_read_buffer_and_stash(char **read_buffer, char **stash);
static char	*extract_line_and_remainder(char **line_to_ret, char **stash,
				char *newline_pointer, char **temp);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*read_buffer;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	while (1)
	{
		read_bytes = read(fd, read_buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free_read_buffer_and_stash(&read_buffer, &stash));
		read_buffer[read_bytes] = '\0';
		if (read_bytes == 0)
			break ;
		ft_strjoin_and_free(&read_buffer, &stash);
		if (!stash)
			return (free(read_buffer), NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(read_buffer);
	return (return_handler(&stash));
}

static char	*free_read_buffer_and_stash(char **read_buffer, char **stash)
{
	free(*read_buffer);
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

/* takes the buffer and the stash and stringjoins them.
this string is stored in the static stash */
static void	ft_strjoin_and_free(char **read_buffer, char **stash)
{
	char	*temp;

	temp = ft_strjoin(*stash, *read_buffer);
	free(*stash);
	if (!temp)
	{
		*stash = NULL;
		return ;
	}
	*stash = temp;
}

/* sets the newline_pointer and calls extract_line_and_remainder
including safety checks */
static char	*return_handler(char **stash)
{
	char	*newline_pointer;
	char	*line_to_ret;
	char	*temp;

	if (!(*stash) || (*stash)[0] == '\0')
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	newline_pointer = ft_strchr(*stash, '\n');
	if (!newline_pointer)
	{
		line_to_ret = *stash;
		*stash = NULL;
		return (line_to_ret);
	}
	return (extract_line_and_remainder(&line_to_ret, stash, newline_pointer,
			&temp));
}

/* helper function that splits the stash and returns the characters up to \n
(the line to be returned). the remainder (stuff after \n) will get stored in
the static variable stash*/
static char	*extract_line_and_remainder(char **line_to_ret, char **stash,
		char *newline_pointer, char **temp)
{
	*line_to_ret = ft_substr(*stash, 0, (newline_pointer - *stash) + 1);
	if (!*line_to_ret)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	*temp = ft_substr(*stash, (newline_pointer - *stash) + 1, ft_strlen(*stash)
			- (newline_pointer - *stash + 1));
	if (!*temp)
	{
		free(*line_to_ret);
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	free(*stash);
	*stash = *temp;
	return (*line_to_ret);
}
/* 
int	main(void)
{
	int i = 0;
	int fd;
	char *p;

	//fd = open();
	//fd = open("test.txt", O_RDONLY);
	fd = open("gnl_edge_cases.txt", O_RDONLY);
	//fd = open("empty.txt", O_RDONLY);
	//fd = open("newline.txt", O_RDONLY);
	while (1)
	{
		p = get_next_line(fd);
		if (!p)
			break ;
		printf("Line %d: '%s'", i + 1, p);
		free(p);
		i++;
	}
} */