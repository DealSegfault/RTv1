#include "rt.h"

void ft_lstpush(t_list **alst, t_list *new)
{
    t_list *temp;

	new->next = NULL;
	if (!*alst)
	{
		*alst = new;
		return;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void    getNodesByName(xmlNodePtr cur, char *node_name, t_list **lst)
{
	t_list *new;
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)node_name)))
		{
			printf("added node : %s\n",cur->name);
			new = ft_lstnew((void *)cur, sizeof(*cur));
			ft_lstpush(lst, new);
		}
		getNodesByName(cur->children, node_name, lst);
		cur = cur->next;
	}
}

xmlDocPtr getdoc(char *docname)
{
    xmlDocPtr doc;

    doc = xmlReadFile(docname, NULL, XML_DOC_DTDVALID);
    if (doc == NULL ) {
        ft_putendl_fd("Wrong xml file\n", STD_ERR);
		return (NULL);
    }
    return (doc);
}

t_list *getObjectNodes(xmlDocPtr doc)
{
	t_list *lst;

	if (!doc)
		return (NULL);
	getNodesByName(xmlDocGetRootElement(doc), "sphere", &lst);
	getNodesByName(xmlDocGetRootElement(doc), "plan", &lst);
	getNodesByName(xmlDocGetRootElement(doc), "cylindre", &lst);
	getNodesByName(xmlDocGetRootElement(doc), "cone", &lst);
	return (lst);
}

int count_nodes(xmlNodePtr first_node)
{
	int i;

	i = 0;
	if (!first_node)
		return (i);
	while (first_node)
	{
		first_node = first_node->next;
		i++;
	}
	return (i);
}