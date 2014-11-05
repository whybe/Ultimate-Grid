/*************************************************************************
				Class Implementation : CUGCTMail
**************************************************************************
	Source file : UGCTMail.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTMail.h"
#include "UGStrOp.h"

#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Using an anonymous namespace to hide the import of this method from the interface
// It's imported this way so people with VC6 and no SDK update can use it
// ( it still requires Windows 98, however )
namespace
{
	typedef BOOL ( __stdcall *TransparentBltProc)(IN HDC,IN int,IN int,IN int,
                            IN int,IN HDC,IN int,IN int,IN int,IN int,IN UINT);

	 HINSTANCE   hModule = NULL;

	 TransparentBltProc pTransBlt = NULL;

	 BOOL TransBlt(HDC hdc, int x, int y, int width, int height, HDC src, int srcX, int srcY, int srcWidth, int srcHeight, COLORREF bkCol)
	 {
		 if (!hModule)
			 hModule = LoadLibrary(_T("MSIMG32.DLL"));
		 if (hModule && !pTransBlt) 
			 pTransBlt = (TransparentBltProc) GetProcAddress(hModule, "TransparentBlt");
		 
		 if(pTransBlt)
			 return (*pTransBlt)(hdc,x,y,width,height,src,srcX,srcY,srcWidth,srcHeight,bkCol);
		 else
			 return FALSE;
	 }

	 // These values are used to set the position of the left icon.
	 const int leftIconTopMargin = 5;
	 const int leftIconLeftMargin = 5;
	 const int leftIconRightMargin = 7;
}

/***************************************************
CUGCTMail - Constructor
	Initialize member variables
****************************************************/
CUGCTMail::CUGCTMail() : m_whiteBrush(RGB(255, 255, 255)), m_bluePen(PS_SOLID, 1, RGB(234, 225, 226)),
						 m_blueBrush(RGB(49, 106, 197))
{
	// NOTE: This code would need to change if the image size changed 
	// ( if it's used by someone moving away from the sample for their own app. )
	m_leftImages.Create(17, 15, ILC_COLOR24 | ILC_MASK, 0, 10);
	m_fontNormal.CreateFont( 14, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Arial" ) );
	m_fontBold.CreateFont( 14, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Arial" ) );
	m_defaultFlagIndex = m_checkIndex = -1;
}

/***************************************************
~CUGCTMail - Destructor
	Clean up all allocated resources
****************************************************/
CUGCTMail::~CUGCTMail()
{
}

/***************************************************
OnDraw
	The Ultimate Grid calls this visual function
	every time it is drawing a cell.  It is up to
	the individual cell type to properly draw itself.
Params:
	dc		- device context to draw the cell with
	rect	- rectangle to draw the cell in
	col		- column that is being drawn
	row		- row that is being drawn
	cell	- cell that is being drawn
	selected- TRUE if the cell is selected, otherwise FALSE
	current - TRUE if the cell is the current cell, otherwise FALSE
Return
	<none>
****************************************************/
void CUGCTMail::OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current)
{

	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	CBrush * pOldBrush = dc->SelectObject( (selected || current) ? &m_blueBrush : &m_whiteBrush);
	int backgroundMode = dc->GetBkMode();
	dc->SetBkMode(TRANSPARENT);

	dc->FillRect(rect, (selected || current) ? &m_blueBrush : &m_whiteBrush);

	mailItem item = ParseString(cell);

	// Draw left icon
	POINT ptLeftIcon;
	ptLeftIcon.x = rect->left + leftIconLeftMargin;
	ptLeftIcon.y = rect->top + leftIconTopMargin;

	m_leftImages.SetBkColor( (selected || current)  ? RGB(46,106,197) : RGB(255,255,255));
	m_leftImages.Draw(dc, item.leftIcon, ptLeftIcon, ILD_NORMAL);

	// Need to fill the background for the left images, because we can't transparently draw 24 bit images from an image list.
	IMAGEINFO iiLeft;

	if (m_leftImages.m_hImageList)
	{
	m_leftImages.GetImageInfo(item.leftIcon, &iiLeft);
	}
	else
	{
		iiLeft.rcImage.left = iiLeft.rcImage.right = iiLeft.rcImage.top = iiLeft.rcImage.bottom = 0;
	}

	IMAGEINFO iiRight;
	iiRight.rcImage.left = iiRight.rcImage.right = iiRight.rcImage.top = iiRight.rcImage.bottom = 0;
	if (m_rightImages.m_hImageList)
	{
	// Draw right image
	m_rightImages.GetImageInfo(item.rightIcon, &iiRight);

	POINT ptRightIcon;
	ptRightIcon.x = rect->right - iiRight.rcImage.right + iiRight.rcImage.left;
	ptRightIcon.y = rect->top;

	m_rightImages.Draw(dc, item.rightIcon, ptRightIcon, ILD_TRANSPARENT);
	}

	// Draw text
	CFont * pOldFont = dc->SelectObject((item.isRead) ? &m_fontNormal : &m_fontBold);
	COLORREF oldTextCol = dc->SetTextColor((selected || current) ? RGB(255, 255, 255) : RGB(0,0,0));

	RECT rcText = *rect;
	rcText.top += 4;
	rcText.right -=  iiRight.rcImage.right - iiRight.rcImage.left;
	rcText.left += iiLeft.rcImage.right - iiLeft.rcImage.left + leftIconLeftMargin + leftIconRightMargin;

	dc->DrawText(item.sender, &rcText, DT_END_ELLIPSIS);
	CSize szDate = dc->GetTextExtent(item.dateString);
	CSize szSender = dc->GetTextExtent(item.sender);
	
	RECT rc = rcText;
	rc.left = rc.right - szDate.cx - 4;

	if (rc.left < rcText.left + szSender.cx + 4)
	{
		rc.left = rcText.left + szSender.cx + 4;
	}

	dc->DrawText(item.dateString, &rc, DT_END_ELLIPSIS);

/*	if (item.attachmentPath.GetLength() && m_attachmentImage.m_hObject)
	{
		BITMAP bm;
		m_attachmentImage.GetBitmap(&bm);
		rc.right -= bm.bmWidth;
	}
*/
	rc.left = rcText.left;
	rc.top = rc.bottom - (szDate.cy + 4);
	
	if (item.attachmentPath.GetLength())
	{
		if (m_attachmentImage.m_hObject)
		{
	        	BITMAP bm;
	        	m_attachmentImage.GetBitmap(&bm);
	        	rc.right -= bm.bmWidth;

	        	CDC dcImg;
	        	dcImg.CreateCompatibleDC(dc);
	        	CBitmap * pOldBitmap = dcImg.SelectObject(&m_attachmentImage);

	        	if (!TransBlt(*dc, rc.right, rect->bottom - bm.bmHeight, bm.bmWidth, bm.bmHeight, dcImg, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255)))
	        	{
			// This probably means we're running on W95
	        		dc->BitBlt(rc.right, rect->bottom - bm.bmHeight, bm.bmWidth, bm.bmHeight, &dcImg, 0, 0, SRCCOPY);
	        	}
		
        		dcImg.SelectObject(pOldBitmap);
        	}
	}

	dc->SelectObject(&m_fontNormal);
	dc->DrawText(item.subject, &rc, DT_END_ELLIPSIS);

	// Line across the bottom
	dc->MoveTo(rect->left, rect->bottom-1);
	dc->SelectObject(&m_bluePen);
	dc->LineTo(rect->right-1, rect->bottom-1);
	dc->LineTo(rect->right-1, rect->top);
	dc->SelectObject(pOldBrush);
	dc->SetTextColor(oldTextCol);
	dc->SetBkMode(backgroundMode);
}

/***************************************************
OnRClicked - is called whenever a cell of this type
is right clicked.  In this case, we use the built in
notification to send a message to our grid-derived 
class, letting it know if we clicked over the right
most icon, or on the rest of the cell, this then
controls which context menu is shown.
****************************************************/

BOOL CUGCTMail::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point)
{
	if (m_rightImages.m_hImageList)
	{
	CUGCell cell;
	m_ctrl->GetCell(col, row, &cell);
	mailItem item = ParseString(&cell);
	IMAGEINFO ii;
	m_rightImages.GetImageInfo(item.rightIcon, &ii);

	if (updn && point->x > rect->right - ii.rcImage.right + ii.rcImage.left && m_defaultFlagIndex >=0 && m_checkIndex >= 0)
	{
			m_ctrl->OnCellTypeNotify(m_ID, col, row, 0, (LONG_PTR)point);

			return TRUE;
		}
	}

	// Mouse was not over the right icon
	m_ctrl->OnCellTypeNotify(m_ID, col, row, 1, (LONG_PTR)point);

	return TRUE;
}

/***************************************************
OnLClicked - is called whenever a cell of this type
is left clicked.  We respond to this event by working
out if the cell has been clicked over the right most 
icon, and if so, we change the flag state.
****************************************************/
BOOL CUGCTMail::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point)
{
	BOOL retval = FALSE;

	CUGCell cell;
	m_ctrl->GetCell(col, row, &cell);

	mailItem item = ParseString(&cell);
	IMAGEINFO ii;
	if (m_rightImages.m_hImageList)
	{
	m_rightImages.GetImageInfo(item.rightIcon, &ii);

	if (updn && point->x > rect->right - ii.rcImage.right + ii.rcImage.left && m_defaultFlagIndex >=0 && m_checkIndex >= 0)
	{
		if (item.rightIcon != m_defaultFlagIndex) 
		{
			item.rightIcon = m_defaultFlagIndex;
		}
		else
		{
			item.rightIcon = m_checkIndex;
		}

		SetString(item, col, row, &cell);

		m_ctrl->OnCellTypeNotify(m_ID, col, row, 2, 0);

		m_ctrl->Invalidate();

		retval = TRUE;
      	}
	}

	return retval;
}


/***************************************************
SetString
	We store all the information relating to an
	item of mail in the mailItem struct, which in
	turn is stored in the text of our cell.  There
	are two SetString functions, one is static and 
	is called from the main grid class.  Both take
	a mailItem struct and turn it into a suitably
	encoded string, and set that string to the cell.
Params:
	item	- mailitem to turn into a string
	col		- column to store string to
	row		- row to store string to
	cell	- cell that is being set
	ctrl	- a pointer to the grid in use 
			  ( used by the static version )
Return
	<none>
****************************************************/
void CUGCTMail::SetString(CUGCTMail::mailItem item, int col, int row, CUGCell * cell, CUGCtrl * ctrl)
{
#ifdef _UNICODE
	std::wstringstream ss;
#else
	std::ostringstream ss;
#endif
	ss << item.leftIcon << '\v';
	ss << item.sender.GetBuffer(item.sender.GetLength()) << '\v';
	item.sender.ReleaseBuffer();
	ss << item.date.GetTime() << '\v';
	ss << item.subject.GetBuffer(item.subject.GetLength()) << '\v';
	item.subject.ReleaseBuffer();
	ss << item.rightIcon << '\v';
	ss << (item.isRead) ? '1' : '0';
	ss << '\v';
	ss << item.mail.GetBuffer(item.mail.GetLength());
	item.mail.ReleaseBuffer();
	ss << '\v';
	ss << item.size;
	ss << '\v';
	ss << item.attachmentPath.GetBuffer(item.attachmentPath.GetLength());
	item.attachmentPath.ReleaseBuffer();
	cell->SetText(ss.str().c_str());
	ctrl->SetCell(col, row, cell);
}

/***************************************************
SetString
	We store all the information relating to an
	item of mail in the mailItem struct, which in
	turn is stored in the text of our cell.  There
	are two SetString functions, one is static and 
	is called from the main grid class.  Both take
	a mailItem struct and turn it into a suitably
	encoded string, and set that string to the cell.
Params:
	item	- mailitem to turn into a string
	col		- column to store string to
	row		- row to store string to
	cell	- cell that is being set
Return
	<none>
****************************************************/
void CUGCTMail::SetString(CUGCTMail::mailItem item, int col, int row, CUGCell * cell)
{
#ifdef _UNICODE
	std::wstringstream ss;
#else
	std::ostringstream ss;
#endif
	ss << item.leftIcon << '\v';
	ss << item.sender.GetBuffer(item.sender.GetLength()) << '\v';
	item.sender.ReleaseBuffer();
	ss << item.date.GetTime() << '\v';
	ss << item.subject.GetBuffer(item.subject.GetLength()) << '\v';
	item.subject.ReleaseBuffer();
	ss << item.rightIcon << '\v';
	ss << (item.isRead) ? '1' : '0' << '\v';
	ss << item.mail.GetBuffer(item.mail.GetLength());
	item.mail.ReleaseBuffer();
	ss << '\v';
	ss << item.size;
	ss << '\v';
	ss << item.attachmentPath.GetBuffer(item.attachmentPath.GetLength());
	item.attachmentPath.ReleaseBuffer();
	cell->SetText(ss.str().c_str());
	m_ctrl->SetCell(col, row, cell);
}

/***************************************************
ParseString
	The ParseString function pulls the text out of a 
	cell, and attempts to parse it into a mailItem struct.
	It will continue trying to find valid values until
	it fails, and then return the struct with whatever
	values it could find.  Naturally, it's always the
	intention that all the required data is present.
Params:
	item	- mailitem to turn into a string
	col		- column to store string to
	row		- row to store string to
	cell	- cell that is being set
Return
	<none>
****************************************************/
CUGCTMail::mailItem CUGCTMail::ParseString(CUGCell * cell)
{
	mailItem item;

	CString sItem;
	cell->GetText(&sItem);

	LPTSTR text = sItem.GetBuffer(sItem.GetLength());
	sItem.ReleaseBuffer();

	TCHAR * nextToken;
	TCHAR * s = UGStr::tcstok(text, _T("\v"), &nextToken);

	if (s)
	{
		item.leftIcon = _ttoi(s);
		s = UGStr::tcstok(NULL, _T("\v"), &nextToken);
		if (s)
		{
			item.sender = s;
			s = UGStr::tcstok(NULL, _T("\v"), &nextToken);
			if (s)
			{
				time_t ltime;
				time(&ltime);

				CTime dateNow(ltime);

				item.date = CTime((time_t)_ttoi(s));

				if (item.date.GetDay() == dateNow.GetDay() &&
					item.date.GetMonth() == dateNow.GetMonth() &&
					item.date.GetYear() == dateNow.GetYear())
				{
					item.dateString = item.date.Format("%I:%M %p");
				}
				else
				{
					item.dateString = item.date.Format("%a %I:%M %p");
				}

				s = UGStr::tcstok(NULL, _T("\v"), &nextToken);
				if (s)
				item.subject = s;
				s = UGStr::tcstok(NULL, _T("\v"), &nextToken);
				if (s)
				{
					item.rightIcon = _ttoi(s);
					s = UGStr::tcstok(NULL, _T("\v"), &nextToken);
					if (s)
					{
						item.isRead = (_ttoi(s) > 0);
						s = UGStr::tcstok(NULL, _T("\v"), &nextToken);
						if (s)
						{
							item.mail = s;
							s = UGStr::tcstok(NULL, _T("\v"), &nextToken);
							if (s)
							{
								// It is acceptable for the attachment path to be empty
								item.didParseOK = true;
								item.size = _ttoi(s);
								s = UGStr::tcstok(NULL, _T("\v"), &nextToken);
								if (s)
								{
									item.attachmentPath = s;
								}
							}
						}
					}
				}
			}
		}

	}
	else
	{
		item.subject = text;
	}

	return item;
}


/***************************************************
AddImage
	This cell type contains two image 
	lists, as we draw icons on both 
	sides of the cell.  This function
	adds a single image to an existing
	image list.  The image list would 
	need to be initialised with the 
	correct image format in the constructor
	for this class.
Params:
	bmp		- the bitmap to add to an image list
	addTo	- an enum value, specifying what list to add to
	mask	- the color to use to generate a mask
Return
	the index of the newly added image.
****************************************************/
int CUGCTMail::AddImage(CBitmap * bmp, AddToImageList addTo, COLORREF mask)
{
	int retval = 0;

	switch(addTo)
	{
	case left:
		retval = m_leftImages.Add(bmp, mask);
		break;
	case right:
		retval = m_rightImages.Add(bmp, mask);		
		break;

	}

	return retval;
}

/***************************************************
AddImageList
	This cell type contains two image 
	lists, as we draw icons on both 
	sides of the cell.  This function
	replaces an existing image list with
	an image list from the resources for
	the project that it's being used in.
Params:
	resourceID	- the ID of the resource imagelist to use
	width		- the width of each image in the list
	addTo		- the image list to replace
	mask		- the color to use to generate a mask
Return
	a bool to indicate success or failure
****************************************************/
bool CUGCTMail::AddImageList(UINT resourceID, int width, AddToImageList addTo, COLORREF mask)
{
	bool success = false;

	if (addTo == left)
	{
		if (m_leftImages.GetSafeHandle())
		{
			m_leftImages.DeleteImageList();
		}

		CBitmap bm;
		bm.LoadBitmap(resourceID);

		BITMAP b;
		bm.GetBitmap(&b);

		const int imageCount = b.bmWidth / width;

		success = (m_leftImages.Create(width, b.bmHeight, ILC_COLOR32, imageCount, imageCount) > 0);

		if (success)
		{
			CDC dc;
			dc.CreateCompatibleDC(NULL);

			CDC srcDC;
			srcDC.CreateCompatibleDC(&dc);
			CBitmap * pOldSrcBmp = srcDC.SelectObject(&bm);

			for(int i=0;i<=imageCount; ++i)
			{
				CBitmap bitmap;
				bitmap.CreateBitmap(width, b.bmHeight, 1, 32, NULL);
				CBitmap * pOldDestBmp = dc.SelectObject(&bitmap);

				dc.BitBlt(0, 0, width, b.bmHeight, &srcDC, width * i, 0, SRCCOPY);
				
				dc.SelectObject(pOldDestBmp);
			 	
				m_leftImages.Add(&bitmap, mask);
			}

			srcDC.SelectObject(pOldSrcBmp);
		}
	}
	else
	{
		if (m_rightImages.GetSafeHandle())
		{
			m_rightImages.DeleteImageList();
		}


		CBitmap bm;
		bm.LoadBitmap(resourceID);

		BITMAP b;
		bm.GetBitmap(&b);

		const int imageCount = b.bmWidth / width;

		success = (m_rightImages.Create(width, b.bmHeight, ILC_COLOR32, imageCount, imageCount) > 0);

		if (success)
		{
			CDC dc;
			dc.CreateCompatibleDC(NULL);

			CDC srcDC;
			srcDC.CreateCompatibleDC(&dc);
			CBitmap * pOldSrcBmp = srcDC.SelectObject(&bm);

			for(int i=0;i<=imageCount; ++i)
			{
				CBitmap bitmap;
				bitmap.CreateBitmap(width, b.bmHeight, 1, 32, NULL);
				CBitmap * pOldDestBmp = dc.SelectObject(&bitmap);

				dc.BitBlt(0, 0, width, b.bmHeight, &srcDC, width * i, 0, SRCCOPY);
				
				dc.SelectObject(pOldDestBmp);
			 	
				m_rightImages.Add(&bitmap, mask);
			}

			srcDC.SelectObject(pOldSrcBmp);
		}
	}

	return success;
}

/***************************************************
DoesTextFit
	The tooltips for this cell 
	show the subject line if it
	did not fit in the cell.  This
	helper function checks if a given
	mailItem has a subject line which
	would fit in the given column of
	the grid, taking into account the 
	size of the icons used by the item,
	and the font it would be drawn in.
Params:
	item	- the mail item to measure
	col		- the index of the column to measure for
Return
	a bool to indicate if text will fit or not
****************************************************/
bool CUGCTMail::DoesTextFit(mailItem item, int col)
{
	CDC dc;
	dc.CreateCompatibleDC(NULL);

	CFont * pOldFont = dc.SelectObject(&m_fontNormal);
	CSize szText = dc.GetTextExtent(item.subject);
	dc.SelectObject(pOldFont);

	int width = m_ctrl->GetColWidth(0) - 10;

	IMAGEINFO ii;
	m_leftImages.GetImageInfo(item.leftIcon, &ii);
	width -= (ii.rcImage.right - ii.rcImage.left + leftIconLeftMargin + leftIconRightMargin);

	m_rightImages.GetImageInfo(item.rightIcon, &ii);
	width -= (ii.rcImage.right - ii.rcImage.left);

	return width >= szText.cx;
}