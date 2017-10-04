/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldenblyd <ldenblyd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 21:52:23 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/04 17:02:38 by ldenblyd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	c = 0;
	if (little[0] == '\0')
		return (char*)(big);
	while (big[i] != '\0')
	{
		j = i;
		c = 0;
		while (big[j] == little[c])
		{
			j++;
			c++;
			if (little[c] == '\0')
				return (char*)(&big[i]);
		}
		i++;
	}
	return (NULL);
}
