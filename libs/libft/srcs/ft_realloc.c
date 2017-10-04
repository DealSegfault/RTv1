/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldenblyd <ldenblyd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:08:34 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/04 17:02:38 by ldenblyd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char *new;

	if (ptr == NULL)
		return (NULL);
	if (!size && ptr != NULL)
	{
		if ((new = (char *)malloc(1)) == NULL)
			return (NULL);
		free(ptr);
		return (new);
	}
	if ((new = (char *)malloc(size)) == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new, ptr, size);
		free(ptr);
	}
	return (new);
}
