#include "rt.h"

static int DTDValidate(xmlDocPtr doc, char *dtd_file_name, int print_errors)
{
	int ret;
	xmlDtdPtr dtd;
	xmlValidCtxtPtr vctxt;

	if ((dtd = xmlParseDTD(NULL, BAD_CAST dtd_file_name)) == NULL)
		return (-1);
	if ((vctxt = xmlNewValidCtxt()) == NULL)
	{
		xmlFreeDtd(dtd);
		return (-1);
	}
	if (print_errors)
	{
		vctxt->userData = (void *) stderr;
		vctxt->error = (xmlValidityErrorFunc) fprintf;
		vctxt->warning = (xmlValidityWarningFunc) fprintf;
	}
	ret = xmlValidateDtd(vctxt, doc, dtd);
	xmlFreeValidCtxt(vctxt);
	xmlFreeDtd(dtd);
	return (ret);
}

static	xmlSchemaPtr getXSDSchema(char *XMLSchemaFile_pathname)
{
	xmlSchemaPtr ptr_schema;
	xmlSchemaParserCtxtPtr ptr_ctxt;

	ptr_schema = NULL;
	ptr_ctxt = xmlSchemaNewParserCtxt(XMLSchemaFile_pathname);
	xmlSchemaSetParserErrors(ptr_ctxt, (xmlSchemaValidityErrorFunc) fprintf,
							 (xmlSchemaValidityWarningFunc) fprintf,
							 stderr);

	ptr_schema = xmlSchemaParse(ptr_ctxt);
	xmlSchemaFreeParserCtxt(ptr_ctxt);
	return (ptr_schema);
}

static int XSDValidate(char *XMLSchemaFile_pathname, xmlDocPtr doc)
{
	xmlSchemaPtr ptr_schema;
	xmlSchemaValidCtxtPtr ptr_validctxt;
	int vl_return;

	ptr_schema = getXSDSchema(XMLSchemaFile_pathname);
	if (!ptr_schema)
		return (xsd_read_error());
	if (doc)
	{
		ptr_validctxt = xmlSchemaNewValidCtxt(ptr_schema);
		xmlSchemaSetValidErrors(ptr_validctxt,
								(xmlSchemaValidityErrorFunc) fprintf,
								(xmlSchemaValidityWarningFunc) fprintf, stderr);
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

int doChecks(xmlDocPtr doc)
{
	xmlValidCtxtPtr validCtxtPtr;

	validCtxtPtr = xmlNewValidCtxt();
	if (xmlStrcmp(doc->children->name, BAD_CAST ROOT_NAME))
		xml_read_error();
	return (DTDValidate(doc, RT_DTD, 1) && XSDValidate(RT_XSD, doc)) ? 1 : 0;
}