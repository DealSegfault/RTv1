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

t_size ft_lstlen(t_list *lst)
{
	size_t len;
	
	len++;
	if (!lst)
		return (-1);
	while (lst)
	{
		len++;
		lst = lst->next;	
	}
	return(len;)
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
	//TODO: Add complex objects
	return (lst);
}

t_obj parse_obj(t_list *lst)
{
	xmlNodePtr node;

	node = (xmlNodePtr)lst->content;
	if(!xmlStrcmp((node->name, ))
}

void create_objs(t_rt *e, t_list *lst)
{
	int i;

	i = 0;
	e->scene->obj = (t_obj *)malloc(sizeof(t_obj) * ft_lstlen(lst) + 1);
	if (!e->scene->obj)
		exit(ERR);
	e->scene->obj[ft_lstlen(lst)] == NULL;
	while (lst)
	{
		COBJ = parse_obj(lst);
		lst = lst->next;
		i++;
	}
}

int parse_obj(t_rt *e, char *path)
{
	xmlDocPtr doc;
	t_list lst_obj;

	//on recupere le doc
	if (!(doc = getdoc(path)))
		return(-1);
		//on envoi l'erreur
	//on lance les checks
	if (!doChecks(doc))
		return(0);
	lst = getObjectNodes(doc);
	create_objs(e, lst);
	return (1);
			//on envoie l'erreur
			//on recup les objets
				//on crée les objets
					//on les add a l'env
}