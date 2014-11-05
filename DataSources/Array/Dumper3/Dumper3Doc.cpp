// Dumper3Doc.cpp : implementation of the CDumper3Doc class
//

#include "stdafx.h"
#include "Dumper3.h"

#include "Dumper3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDumper3Doc

IMPLEMENT_DYNCREATE(CDumper3Doc, CDocument)

BEGIN_MESSAGE_MAP(CDumper3Doc, CDocument)
	//{{AFX_MSG_MAP(CDumper3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumper3Doc construction/destruction

CDumper3Doc::CDumper3Doc()
{
	// TODO: add one-time construction code here

}

CDumper3Doc::~CDumper3Doc()
{
}

BOOL CDumper3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDumper3Doc serialization

void CDumper3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		char buf[1000];
		int nBytesRead;

		while(1) {
			nBytesRead = ar.Read(buf, 1000);
			if (0 == nBytesRead) {
				break;
			}
			else {
				for(int i = 0; i < nBytesRead; i++)
					m_byteArray.Add(buf[i]);


			}
			if (1000 > nBytesRead) {
   				break;
			}
		}

	}
}

/////////////////////////////////////////////////////////////////////////////
// CDumper3Doc diagnostics

#ifdef _DEBUG
void CDumper3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDumper3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDumper3Doc commands
