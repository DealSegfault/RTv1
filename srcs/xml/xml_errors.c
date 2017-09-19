#include "rt.h"

int	xsd_read_error()
{
	ft_putendl_fd("Could not open XML Schema", STD_ERR);
	xmlCleanupParser();
	xmlMemoryDump();
	return (-1);
}

void xml_read_error()
{
	ft_putendl_fd("Wrong xml file\n", STD_ERR);
	exit(-1);
}