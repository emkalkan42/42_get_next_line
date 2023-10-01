/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:12:14 by emkalkan          #+#    #+#             */
/*   Updated: 2023/09/27 15:49:32 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
*	GET_NEXT_LINE
*	-------------
*	DESCRIPTION
*	This function takes an opened file descriptor 
	and returns its next line.
*	This function has undefined behavior when 
	reading from a binary file.
*	PARAMETERS
*	#1. A file descriptor 
*	RETURN VALUES
*	If successful, get_next_line returns a string 
	with the full line ending in
*	a line break (`\n`) when there is one. 
*	If an error occurs, or there's nothing more 
	to read, it returns NULL.
*	--------------------------------------------
*	AUXILIARY FUNCTIONS
*	-------------------
*	READ_TO_LEFT_STR
*	-----------------
*	DESCRIPTION
*	Takes the opened file descriptor and saves 
on a "buff" variable what readed
*	from it. Then joins it to the cumulative 
static variable for the persistence
*	of the information.
*	PARAMETERS
*	#1. A file descriptor.
*	#2. The pointer to the cumulative static 
variable from previous runs of
*	get_next_line.
*	RETURN VALUES
*	The new static variable value with buffer 
joined for the persistence of the info,
*	or NULL if error.
*/

#include "get_next_line.h"
#include <unistd.h>
//#include <stdio.h>
//#include <fcntl.h>

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	// Allocate memory for a buffer to read data from the file descriptor
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	// Initialize the read_bytes counter
	rd_bytes = 1;
	// Continue reading and appending data to left_str until a newline is found or EOF is reached
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		// Read data from the file descriptor into the buffer
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		// Null-terminate the buffer to make it a valid C string
		buff[rd_bytes] = '\0';

		// Append the buffer's content to the existing data in left_str
		left_str = ft_strjoin(left_str, buff);
	}
	// Free the buffer and return the updated left_str
	free(buff);
	return (left_str);
}
char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	// Check for invalid file descriptor or negative BUFFER_SIZE
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	// Read data from the file descriptor and accumulate it in left_str
	left_str = ft_read_to_left_str(fd, left_str);
	// If there's an error during reading, return NULL
	if (!left_str)
		return (NULL);
	// Extract a line from left_str
	line = ft_get_line(left_str);
	// Update left_str to remove the extracted line
	left_str = ft_new_left_str(left_str);
	// Return the extracted line
	return (line);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/