// SpeedTestDoc.h : interface of the CSpeedTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPEEDTESTDOC_H__E7C31CA6_C224_4AB4_AB62_C9B0ED5C366F__INCLUDED_)
#define AFX_SPEEDTESTDOC_H__E7C31CA6_C224_4AB4_AB62_C9B0ED5C366F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSpeedTestDoc : public CDocument
{
protected: // create from serialization only
	CSpeedTestDoc();
	DECLARE_DYNCREATE(CSpeedTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeedTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpeedTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpeedTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEEDTESTDOC_H__E7C31CA6_C224_4AB4_AB62_C9B0ED5C366F__INCLUDED_)
