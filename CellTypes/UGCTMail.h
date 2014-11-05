/*************************************************************************
				Class Declaration : CUGCTAutoSize
**************************************************************************
	Source file : UGCTAutoSize.cpp
	Header file : UGCTAutoSize.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose:
		The CUGCTAutoSize celltype extends the standard celltype providing
		funcitonality to size its cell to make sure that cell's data is
		visible in full.  It will not make columns or rows smaller,
		but it will enlarge them whenever needed.
	
	Details:
		This celltype does not send any notifications to the CUGCtrl derived
		classes.
*************************************************************************/
#ifndef _UGCTMail_H_
#define _UGCTMail_H_

#include <time.h>


class UG_CLASS_DECL CUGCTMail: public CUGCellType
{
public:

	struct mailItem
	{
		mailItem::mailItem()
		{
			leftIcon = -1;
			sender = "";
			dateString = "";
			subject = "";
			rightIcon = -1;
			isRead = false;
			mail = "";
			size = 0;
			attachmentPath = "";
			didParseOK = false;
		}

		int		leftIcon;
		CString sender;
		CString dateString;
		CString subject;
		int		rightIcon;
		bool	isRead;
		CString	mail;
		CTime	date;
		bool	didParseOK;
		CString	attachmentPath; // "" == no attachment
		int		size;
	};

protected:

public:
	CUGCTMail();
	~CUGCTMail();
	
	enum AddToImageList { left, right};
	int AddImage(CBitmap * bmp, AddToImageList addTo, COLORREF mask = RGB(255, 0,255));
	bool AddImageList(UINT resourceID, int width, AddToImageList addTo, COLORREF mask = RGB(255, 0,255));

	void SetAttachmentImage(HBITMAP img) { m_attachmentImage.Attach(img); }

	int  GetDefaultFlagIndex() { return m_defaultFlagIndex; }
	void SetDefaultFlagIndex(int flag) { m_defaultFlagIndex = flag; }
	void SetCheckIndex(int check) { m_checkIndex = check; }
	bool DoesTextFit(mailItem item, int col = 0);

	static mailItem ParseString(CUGCell * cell);
	static void SetString(mailItem item, int col, int row, CUGCell * cell, CUGCtrl * ctrl);
private:
	void SetString(mailItem item, int col, int row, CUGCell * cell);

	// Overrides
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnRClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);

	// member variables
	CBrush		m_whiteBrush;
	CPen		m_bluePen;
	CBrush		m_blueBrush;
	CFont		m_fontNormal;
	CFont		m_fontBold;

	CImageList	m_leftImages;
	CImageList	m_rightImages;

	int			m_defaultFlagIndex;
	int			m_checkIndex;

	CBitmap		m_attachmentImage;
};

#endif // _UGCTMail_H_