/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:24 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 01:43:59 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	ft_strlen_gnl(const char *s)
{
	int	len;

	len = 0;
	if (s)
	{
		while (s[len] != '\0')
			len++;
	}
	return (len);
}

static void	ft_perform_join(char *dest, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			dest[j++] = s1[i++];
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			dest[j++] = s2[i++];
	}
	dest[j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL)
		len1 = 0;
	else
		len1 = ft_strlen_gnl(s1);
	if (s2 == NULL)
		len2 = 0;
	else
		len2 = ft_strlen_gnl(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	ft_perform_join(str, s1, s2);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (char)c)
		if (!*s++)
			return (NULL);
	return ((char *)s);
}
