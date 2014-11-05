#include "ugctrl.h"
#include "UGCBADSC.h"


class MyCug:public CUGCtrl
{

public:

	CFont		m_font;
	CFont		m_printFont;
	CPen		m_borderPen;

	CUGCBArrayDataSource	m_data;

	MyCug();
	~MyCug();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
};
