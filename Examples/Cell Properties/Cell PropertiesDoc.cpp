// Cell PropertiesDoc.cpp : implementation of the CCellPropertiesDoc class
//

#include "stdafx.h"
#include "Cell Properties.h"

#include "Cell PropertiesDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCellPropertiesDoc

IMPLEMENT_DYNCREATE(CCellPropertiesDoc, CDocument)

BEGIN_MESSAGE_MAP(CCellPropertiesDoc, CDocument)
END_MESSAGE_MAP()


// CCellPropertiesDoc construction/destruction

CCellPropertiesDoc::CCellPropertiesDoc()
{
	// TODO: add one-time construction code here

}

CCellPropertiesDoc::~CCellPropertiesDoc()
{
}

BOOL CCellPropertiesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCellPropertiesDoc serialization

void CCellPropertiesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CCellPropertiesDoc diagnostics

#ifdef _DEBUG
void CCellPropertiesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCellPropertiesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCellPropertiesDoc commands
