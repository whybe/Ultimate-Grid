// CellTypeOutlook.h: interface for the CCellTypeOutlook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELLTYPEOUTLOOK_H__D784EA52_AE06_40B4_945D_895EBDAA1B6D__INCLUDED_)
#define AFX_CELLTYPEOUTLOOK_H__D784EA52_AE06_40B4_945D_895EBDAA1B6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ugctrl.h"

//cell types
#include "ugctexpand.h"
#include "UGCTMail.h"
#include "UGCTMailSort.h"
#include "UGCTOutlookHeader.h"

class CCellTypeOutlook : public CUGCtrl  
{
public:
	CCellTypeOutlook();
	virtual ~CCellTypeOutlook();
	void SetFlag(int index);
	void SetDefaultFlag(int index);
	void ChangeReadFlag();
	
	void SetMailWindow(CRichEditCtrl* pWnd);

	void SetShowGroups(bool show);
	bool GetShowGroups();

	CUGCTMailSort::sortBy GetSortBy();
	void SetSortBy(CUGCTMailSort::sortBy sort);

	void CollapseAll();
	void ExpandAll();

	void MarkAllRead();
	void MarkAllUnread();

private:
	// CUGExpandType cell type
	CUGExpandType		m_expand;
	int					m_nExpandIndex;

	// CUGOutlookHeader cell type
	CUGCTOutlookHeader  m_header;
	int					m_nHeaderIndex;

	// CUGOutlookMail cell type
	CUGCTMail			m_mail;
	int					m_nMailIndex;

	// CUGMailSort cell type
	CUGCTMailSort		m_mailSort;
	int					m_nMailSortIndex;

	//fonts
	CFont				m_defFont;
	CFont				m_boldFont;
	CFont				m_medFont;
	CFont				m_medBoldFont;
	CFont				m_lrgFont;
	CFont				m_smFont;

	int					m_lastMenuRow;
	// This is used so when we navigate away from an item we just marked as unread,
	// it will stay that way
	bool				m_bMarkedAsUnread;
	CRichEditCtrl *		m_pMailWindow;

	bool				m_bShowGroups;

	// This method calls SortBy then handles the setting up of cell heights and removal/insertion of header cells
	void DoSort();
	// As we need to remove headers to do the sorting, these methods search the sorted rows and reinsert them.
	void InsertHeadersByFlag();
	void InsertHeadersByDate();
	void InsertHeadersByStringProperty();
	void InsertHeadersBySize();
	void InsertHeadersByAttachments();

	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnCellChange(int oldcol,int newcol,long oldrow,long newrow);
	virtual int OnHint(int col,long row,int section,CString *string);
	virtual int OnSortEvaluate( CUGCell* pCell1, CUGCell* pCell2, int iFlags );

	//{{AFX_MSG(CCellTypeDemoGrid)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_CELLTYPEOUTLOOK_H__D784EA52_AE06_40B4_945D_895EBDAA1B6D__INCLUDED_)
