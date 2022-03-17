/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:58:44 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/15 05:47:10 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// locate character in string
char	*ft_strchr(const char *s, int c)
{
	char	*p_s;

	p_s = (char *)s;
	while (*p_s != '\0')
	{
		if (*p_s == (char)c)
			return (p_s);
		p_s++;
	}
	if ((char)c == '\0')
		return (p_s);
	return (NULL);
}
