/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:01:12 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 15:03:01 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower(int c)
{
	if ('a' <= c && c <= 'z')
		return (1);
	else
		return (0);
}

// lower case to upper case letter conversion
int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - ('a' - 'A'));
	else
		return (c);
}
