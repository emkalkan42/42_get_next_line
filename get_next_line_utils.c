/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:12:58 by emkalkan          #+#    #+#             */
/*   Updated: 2023/10/01 13:00:02 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	---------
*	GET_LINE
*	---------
*	Extracts the line (ending in either 
	line break and `\0` or only `\0` in EOF)
*	from static variable.
*	PARAMETERS
*	#1. The pointer to the cumulative static 
	variable from previous runs of get_next_line.
*	RETURN VALUES
*	The string with the full line ending in a 
	line break (`\n`) + (`\0`).
*	-------------
*	NEW_LEFT_STR
*	-------------
*	Stores in the cumulative static variable the 
	new updated variable with whatever
*	is left from the original, minus the line extracted.
*	PARAMETERS
*	#1. The pointer to the cumulative static variable 
	from previous runs of get_next_line.
*	RETURN VALUES
*	The new updated string with whatever is left from 
	the original static, minus the
*	line extracted.
*/

#include "get_next_line.h"

/*This function calculates the length of a null-terminated string.
It returns the length as a size_t (unsigned integer) value.
Handle the case of a null pointer
Iterate through the string until the null terminator is found
size_t	ft_strlen(char *s)*/

/* This function searches for the first occurrence
of a character 'c' in the string 's'.
It returns a pointer to the first occurrence of
'c' in 's' or a pointer to the null terminator
if 'c' is not found in 's'.*/
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
/* Handle the case of a null pointer
Return a pointer to the null terminator
Return a pointer to the first occurrence of 'c'
'c' was not found in 's'*/

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

/* This function joins two strings together and
returns the result as a new string.
Handle the case of a null pointer by creating an empty string
Handle the case of null pointers
Calculate the length of the new string
Copy characters from 'left_str' to 'str'
Append characters from 'buff' to 'str'
Null-terminate the new string
Free the memory allocated for 'left_str'
Return the concatenated string*/
char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

/* This function extracts a line from 'left_str'
until it encounters a newline character.
It returns the extracted line as a new string.
If 'left_str' is empty or contains no newline, return NULL
Calculate the length of the line
Allocate memory for the new line, including the
newline character and null terminator
Copy characters from 'left_str' to 'str' until a
newline or end of 'left_str' is encountered
Null-terminate the new line
Return the extracted line*/
char	*ft_get_line(char *left_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!left_str[i])
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* This function creates a new 'left_str' by removing 
the first line from 'left_str'.
It returns the modified 'left_str'.
Find the position of the first newline character in 'left_str'
No newline found, so 'left_str' is entirely consumed
Allocate memory for the new 'left_str', excluding the 
first line and newline character
Copy characters from 'left_str' after the newline to 'str'
Null-terminate the new 'left_str'
Free the memory allocated for the old 'left_str'
Return the modified 'left_str'*/
char	*ft_new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	free(left_str);
	return (str);
}
