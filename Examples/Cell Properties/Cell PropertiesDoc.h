// Cell PropertiesDoc.h : interface of the CCellPropertiesDoc class
//


#pragma once

class CCellPropertiesDoc : public CDocument
{
protected: // create from serialization only
	CCellPropertiesDoc();
	DECLARE_DYNCREATE(CCellPropertiesDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CCellPropertiesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


