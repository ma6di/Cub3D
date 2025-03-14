/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:19:51 by lsasse            #+#    #+#             */
/*   Updated: 2025/03/03 14:44:13 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlen2(const char *s)
{
    size_t i;
	
	i = 0;

    if (s)  // Check for NULL at the start
    {
        while (s[i])
            i++;
    }
    return i;
}

// static char *ft_strchr2(const char *s, int c)
// {
//     if (!s)  // If s is NULL, return NULL immediately
//         return NULL;

//     if (c == '\0')  // Special case for NULL-terminator
//         return (char *)&s[ft_strlen2(s)];

//     while (*s)  // Iterate through string
//     {
//         if (*s == (char)c)
//             return (char *)s;
//         s++;
//     }

//     return NULL;  // Return NULL if no match found
// }

char *ft_strjoin2(char *archive, const char *buff)
{
    size_t i = 0, j = 0;
    char *str;

    if (!buff)
        return NULL;

    if (!archive) 
    {
        archive = (char *)malloc(1);
        if (!archive)
            return NULL;
        archive[0] = '\0';
    }

    size_t archive_len = ft_strlen2(archive);
    size_t buff_len = ft_strlen2(buff);

    str = (char *)malloc(sizeof(char) * (archive_len + buff_len + 1));
    if (!str)
    {
        free(archive);  // ✅ Free archive before returning NULL
        return NULL;
    }

    while (archive[i])
        str[i] = archive[i], i++;

    while (buff[j])
        str[i++] = buff[j++];

    str[i] = '\0';
    free(archive);  // ✅ Free old archive to prevent leaks

    return str;
}

// Function to update the archive after reading a line
char *update_archive(char *archive)
{
    int i = 0;
    char *new_archive;

    if (!archive || !archive[i])
    {
        free(archive);  // ✅ Free old archive
        return NULL;
    }

    while (archive[i] && archive[i] != '\n')
        i++;

    if (!archive[i])  // ✅ If no newline found, free and return NULL
    {
        free(archive);
        return NULL;
    }

    new_archive = ft_strdup(archive + i + 1);
    free(archive);  // ✅ Free old archive
    return new_archive;
}



// Function to read data into the archive buffer from the file descriptor
char *read_to_archive(int fd, char *archive)
{
    char *buffer;
    char *new_archive;
    int bytes_read;

    // ✅ Allocate buffer safely
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
    {
        printf("Error: malloc failed for buffer\n");
        return (NULL);
    }

    // ✅ Read data safely
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0) // End of file or read error
    {
        free(buffer);
        return (archive);
    }

    buffer[bytes_read] = '\0';  // ✅ Null-terminate buffer

    // ✅ Handle new archive case
    if (!archive)
    {
        archive = ft_strdup(buffer);
        if (!archive) // Check if strdup failed
        {
            printf("Error: malloc failed for archive\n");
            free(buffer);
            return (NULL);
        }
    }
    else
    {
        new_archive = ft_strjoin(archive, buffer);
        if (!new_archive) // Check if strjoin failed
        {
            printf("Error: malloc failed for new_archive\n");
            free(buffer);
            return (NULL);
        }
        free(archive);
        archive = new_archive;
    }

    free(buffer);
    return (archive);
}