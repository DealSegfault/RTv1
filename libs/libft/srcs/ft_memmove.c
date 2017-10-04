/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldenblyd <ldenblyd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:25:06 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/04 17:02:38 by ldenblyd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *c1;
	char *c2;

	if (dst < src)
		return (ft_memcpy(dst, src, len));
	if (dst > src)
	{
		if (len == 0 || dst == src)
			return (dst);
		c1 = (char *)dst;
		c2 = (char *)src;
		while (len--)
		{
			c1[len] = c2[len];
		}
		return (dst);
	}
	return (NULL);
}
