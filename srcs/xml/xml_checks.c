/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agfernan <agfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 22:42:22 by agfernan          #+#    #+#             */
/*   Updated: 2017/09/30 23:24:23 by agfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			dtd_validate(xmlDocPtr doc, char *file, int print_e)
{
	int				ret;
	xmlDtdPtr		dtd;
	xmlValidCtxtPtr	vctxt;

	if ((dtd = xmlParseDTD(NULL, (xmlChar*)file)) == NULL)
		dtd_read_error(dtd);
	if ((vctxt = xmlNewValidCtxt()) == NULL)
		xml_alloc_error();
	if (print_e)
	{
		vctxt->userData = (void *)stderr;
		vctxt->error = (xmlValidityErrorFunc)NULL;
		vctxt->warning = (xmlValidityWarningFunc)NULL;
	}
	ret = xmlValidateDtd(vctxt, doc, dtd);
	xmlFreeValidCtxt(vctxt);
	xmlFreeDtd(dtd);
	return (ret);
}

static xmlSchemaPtr	get_xsd(char *xsd_path)
{
	xmlSchemaPtr			ptr_schema;
	xmlSchemaParserCtxtPtr	ptr_ctxt;

	ptr_schema = NULL;
	ptr_ctxt = xmlSchemaNewParserCtxt(xsd_path);
	xmlSchemaSetParserErrors(ptr_ctxt, (xmlSchemaValidityErrorFunc)NULL,
		(xmlSchemaValidityWarningFunc)NULL, stderr);
	ptr_schema = xmlSchemaParse(ptr_ctxt);
	xmlSchemaFreeParserCtxt(ptr_ctxt);
	return (ptr_schema);
}

static int			xsd_validate(char *xsd_path, xmlDocPtr doc)
{
	xmlSchemaPtr			ptr_schema;
	xmlSchemaValidCtxtPtr	ptr_validctxt;
	int						vl_return;

	ptr_schema = get_xsd(xsd_path);
	if (!ptr_schema)
		return (xsd_read_error());
	if (doc)
	{
		ptr_validctxt = xmlSchemaNewValidCtxt(ptr_schema);
		xmlSchemaSetValidErrors(ptr_validctxt,
								(xmlSchemaValidityErrorFunc)NULL,
								(xmlSchemaValidityWarningFunc)NULL, stderr);
		vl_return = xmlSchemaValidateDoc(ptr_validctxt, doc);
		if (vl_return == 0)
			xmlSchemaFreeValidCtxt(ptr_validctxt);
		if (vl_return == 0)
			return (1);
		else if (vl_return > 0)
			return (0);
		else
			return (-1);
	}
	return (-1);
}

int					do_checks(xmlDocPtr doc)
{
	xmlValidCtxtPtr	vctxt;
	int				dtd;
	int				xsd;

	if (!(vctxt = xmlNewValidCtxt()))
		return (0);
	dtd = dtd_validate(doc, RT_DTD, 1);
	xsd = xsd_validate(RT_XSD, doc);
	return (dtd && xsd) ? 1 : 0;
}
