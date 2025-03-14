/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:14:05 by mcheragh          #+#    #+#             */
/*   Updated: 2025/03/03 14:43:57 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;

	if (!s1) // Handle NULL input safely
		return (NULL);

	// Find length directly in malloc
	for (i = 0; s1[i]; i++)
		;
	
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);

	// Copy string
	for (int j = 0; j <= i; j++) // Includes null terminator
		dst[j] = s1[j];

	return (dst);
}

