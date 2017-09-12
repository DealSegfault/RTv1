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

unsigned int ft_lstlen(t_list *lst)
{
	unsigned int len;
	
	len = 0;
	len++;
	if (!lst)
		return (-1);
	while (lst)
	{
		len++;
		lst = lst->next;	
	}
	return(len);
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

    doc = xmlReadFile(docname, NULL, 0);
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
	lst = NULL;
	getNodesByName(xmlDocGetRootElement(doc), "sphere", &lst);
	getNodesByName(xmlDocGetRootElement(doc), "plan", &lst);
	getNodesByName(xmlDocGetRootElement(doc), "cylindre", &lst);
	getNodesByName(xmlDocGetRootElement(doc), "cone", &lst);
	//TODO: Add complex objects
	return (lst);
}

xmlNodePtr getLights(xmlDocPtr doc)
{
	t_list *lst;
	xmlNodePtr lights;

	getNodesByName(xmlDocGetRootElement(doc), "lights", &lst);
	lights = (xmlNodePtr)lst->content;
	return (lights->children);
}

int			create_obj(xmlNodePtr node)
{
	t_obj new;

	new.is_init = 1;
	new.type = type;
	new.color = c_color(255, 255, 255);
	new.pos = vec_new3(0, 0, 0);
	new.dir = vec_new3(0, 0, 0);
	new.angle = 0;
	new.maxp = vec_new3(0, 0, 0);
	new.minp = vec_new3(0, 0, 0);
	new.r = 0;
	new.t = -1;
	new.mat = create_matiere();
	return (new);
}

int		hasAttr(xmlNode *a_node, xmlChar *attr)
{
	if (!xmlGetProp(a_node, attr))
		return 0;
	return 1;
}


int		parse_obj_node(t_obj *obj, xmlNodePtr node)
{
	*obj.radius = (val(xmlGetProp(node, BAD_CAST"radius"))) ?
}

t_obj	get_obj(xmlNodePtr node)
{
	t_obj new;

	if(!xmlStrcmp(node->name, BAD_CAST"sphere"))
		new = create_obj(SPHERE, e);
	if (!xmlStrcmp(node->name, BAD_CAST"plane"))
		new = create_obj(PLANE, e);
	if (!xmlStrcmp(node->name, BAD_CAST"cone"))
		new = create_obj(CONE, e);
	if (!xmlStrcmp(node->name, BAD_CAST"cylindre"))
		new = create_obj(CYLINDER, e);
	parse_obj_node(&new, node);
	return (new);
}

void create_objs(t_rt *e, t_list *lst)
{
	int i;

	i = 0;
	e->scene.obj = (t_obj *)malloc(sizeof(t_obj) * ft_lstlen(lst) + 1);
	if (!e->scene.obj)
		exit(ERR);
	e->scene.obj[ft_lstlen(lst)] = NULL;
	while (lst)
	{
		e->COBJ = get_obj((xmlNodePtr)lst->content);
		lst = lst->next;
		i++;
	}
	//on recupere le content qu'on converti en xmlNodePtr
	//on crée le type d'objet associé
	//on parse le noeud
}

void ft_lstfree(t_list **lst)
{
	if (*lst)
	{
		ft_lstfree(&((*lst)->next));
		free(*lst);
		*lst = NULL;
	}
}

t_vec3 getVecFromNode(xmlNodePtr node)
{
	t_vec3 new;

	new.x = atof((char *)(xmlGetProp(node, BAD_CAST"x")));
	new.y = atof((char *)(xmlGetProp(node, BAD_CAST"y")));
	new.z = atof((char *)(xmlGetProp(node, BAD_CAST"z")));

	return (new);
}

int	set_camera_xml(t_rt *e, xmlNodePtr cam_node)
{
	xmlNodePtr child;

	camera_create(e);
	child = cam_node->children;
	e->scene.cam.ray.pos = getVecFromNode(child);
	child = child->next;
	e->scene.cam.ray.dir = getVecFromNode(child);
	e->scene.cam.fov = ft_atoi((char *)xmlGetProp(cam_node, BAD_CAST"fov"));
	return (1);
}

int parse_doc(t_rt *e, char *path)
{
	xmlDocPtr doc;
	t_list *lst;

	xmlKeepBlanksDefault(0);
	//on recupere le doc
	if (!(doc = getdoc(path)))
		return(-1);
		//on envoi l'erreur
	//on lance les checks
	if (!doChecks(doc))
		return(0);
	lst = getObjectNodes(doc);
	create_objs(e, lst);
	ft_lstfree(&lst);
	getNodesByName(xmlDocGetRootElement(doc), "camera", &lst);
	set_camera_xml(e, (xmlNodePtr)(lst->content));
	ft_lstfree(&lst);
	return (1);
			//on envoie l'erreur
			//on recup les objets
				//on crée les objets
					//on les add a l'env
}