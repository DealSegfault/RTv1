/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:04:02 by agfernan          #+#    #+#             */
/*   Updated: 2017/09/30 22:48:00 by agfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		xsd_read_error(void)
{
	ft_putendl_fd("Could not open XML Schema", STD_ERR);
	xmlCleanupParser();
	xmlMemoryDump();
	exit(-1);
}

int		dtd_read_error(xmlDtdPtr dtd)
{
	ft_putendl_fd("Could not open DTD file", STD_ERR);
	xmlFreeDtd(dtd);
	exit(-1);
}

void	xml_alloc_error(void)
{
	ft_putendl_fd("An error occured", STD_ERR);
	exit(-1);
}

void	xml_read_error(void)
{
	ft_putendl_fd("Wrong xml file\n", STD_ERR);
	exit(-1);
}
