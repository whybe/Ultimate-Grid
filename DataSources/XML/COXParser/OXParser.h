// //////////////////////////////////////////////////////////////////////////
// Header file : OXParser.h
// Parser.h: interface for the COXParser class.

// Product Version: 7.51

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
//
//////////////////////////////////////////////////////////////////////



// Properties:
//	YES	Abstract class (does not have any objects)
//	NO	Derived from CWnd

//	NO	Is a Cwnd.                     
//	YES	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO 	Needs a resource (template)

//	YES	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////
/*
 Desciption :         

 COXParser is a simple class that allow the parsing of XML-style formatted files
 that contain nested tags, comments, markup and text. Tags are delimited using the 
 usual <...>, </...> format, or <.../> for an empty tag, and each tag can contains 
 one or more attributes (eg <tag value="a" number=1>. Comments delimited by 
 <!-- and --> delimiters are suppored, as is literal text. Markup and processing
 instructions delimited by <!...> and <?...?> respectively is also parsed but not 
 processed.

 This class is only for simple "XML-like" parsing, and does not conform to the
 XML 1.0 specification. See http://www.w3.org/TR/1998/REC-xml-19980210.html
 for the full specs, or http://www.xml.com/xml/pub/98/10/guide1.html for a more
 readable version.

 An example would be:
 
 <XML>
      <Element1>
        <Element1a value=4/>
        <!-- A comment -->>
     </Element1>
     <Element2>
         Some Text
         <Name2a value="6" size="small"/>
     </Level2>
  </XML>

 This would be parsed into the following structure:

                            [Root]
                               |
                              XML
                               |
                -------------------------------
                |                             |
            Element1                       Element2
                |                             |
        --------------                ---------------------
        |            |                |                    |
    Element1a      Comment        Literal Text         Element2a 
  ("value" = 4) ("A comment")    ("Some Text")  ("value"="6", "size"="small") 
 

 Each element can contain a collection of further Elements, and a collection of 
 attribute. Once a file or text buffer has been parsed, the Root Element ("[Root]")
 of the COXParser object will contain the collection  of all elements (in 
 COXParserElement objects) each with their set of attributes (in COXAttribute objects). 
 Each element in the tree will contain further subElements
 (COXParserElement objects), Comments (COXParserObject) and text (COXParserObject).
 All objects contained within the tree are derived from COXParserObject. To
 determine the type of object, use COXParserObject::GetType(). This will return
 UNKNOWN, ELEMENT, PLAINTEXT, COMMENT, MARKUP or ATTRIBUTE.

 Using COXParser:

 To use this class simply declare a variable of type COXParser, then call 
 COXParser::Parse or COXParser::ParseFile. The parser object will then contain
 the tree structure of the text buffer or file. 

 The easiest way to traverse the tree is to use a recursive function:

  void DisplayElement(COXParserElement* pElement)
  {
      if (pElement->GetType() != CParseObject::ELEMENT)
          return;

       printf("%s\n", pElement->GetName());
       
       for (int i = 0; i < pElement->NumAttributes(); i++)
       {
           printf("Name = %s ", pElement->Attribute(i)->GetName());
           
           if (pElement->Attribute(i)->GetAttributeType() == COXAttribute::ATTR_STRING)
               printf("Value = %s\n", pElement->Attribute(i)->GetStringValue());
           else if (pElement->Attribute(i)->GetAttributeType() == COXAttribute::ATTR_INTEGER)
               sprintf("Value = %d\n", pElement->Attribute(i)->GetIntValue());
       }
       
       for (i = 0; i < pElement->NumObjects(); i++)
       {
          CParseObject* pObject = pElement->Object(i);
       
          switch (pObject->GetType())
          {
              case COXParserObject::CDATA:
              case COXParserObject::PLAINTEXT:
                   printf("Text = %s\n", pObject->GetText());
                   break;
    
              case COXParserObject::COMMENT:
                   printf("Comment = %s\n", pObject->GetText());
                   break;
 
              case COXParserObject::MARKUP:
                   printf("Markup = %s\n", pObject->GetText());
                   break;

              case COXParserObject::PROCINSTR:
                   printf("Processing Instruction = %s\n", pObject->GetText());
                   break;

              case COXParserObject::ELEMENT:
                   DisplayElement((COXParserElement*)pObject);
                   break;
          }
       }
   }

 Then:

   COXParser parser;
   parser.ParseFile("file.txt");

   DisplayElement(parser.Root());

  COXParser also allows you to hook in your own error reporting callback. Simply
  call 

       COXParser::SetErrorRptFunction(ReportErrorFn, dwData);

   where ReportErrorFn is a function of type

      BOOL ReportErrorFn(UINT nErrorCode, LPCTSTR szError, int nLine, int nColumn, 
                         DWORD dwData)

   nErrorCode contains an error code. szError contains an error message for line 
   nLine, col nColumn, and dwData is specifed in SetErrorRptFunction and passed to 
   the callback. The return value for this function is not used as yet (In future 
   it will be used to provide control over whether or not processing should be halted).
   You can use LPCTSTR COXParser::TranslateErrorCode() to get a literal representation
   of the errorcode.

   An example of such a function would be
      
      BOOL CMyView::ReportError(UINT nErrorCode, LPCTSTR szError, int nLine, int nColumn, 
                                DWORD dwData)
      {
          CString str;
          LPTSTR szFilename = (LPTSTR)dwData;
      
          if (szFilename)
              str.Format(_T("Error parsing file %s. \nLine %d, Column %d:\n%s"), 
                         szFilename, nLine, nColumn, szError);
          else
              str.Format(_T("Error parsing file. \nLine %d, Column %d:\n%s"), nLine, nColumn, szError);
      
          AfxMessageBox(str, MB_ICONEXCLAMATION);

          return FALSE;
      }


 TODO:
   (These are supported as Markup elements - but further processing could be added)
     Parsing of Element Type Declarations    ie <!ELEMENT oldjoke  (burns+, allen, applause?)>
     Parsing of Attribute List Declarations  ie <!ATTLIST oldjoke  name ID #REQUIRED >
     Entity Declarations                     ie <!ENTITY ATI "ArborText, Inc.">, or
                                                <!ENTITY IncludeStuff SYSTEM "/folder/include.xml">
     Parameter Entities                      ie <!ENTITY % personcontent "#PCDATA | quote">
       ( then <!ELEMENT burns (%personcontent;)*>  is the same as <!ELEMENT burns (#PCDATA | quote)*>
     Notation Declaration                    ie  <!NOTATION' Name Public>

   (This is already supported as a PI - but further processing could be added)
     Add in support for the prolog       ie  <?xml version=1.0 encoding='UTF-8' standalone='yes' ?>'
 
    Name validation (eg only certain chars allowed in names and tokens)
*/


#if !defined(_OXPARSER_H__)
#define _OXPARSER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXDllExt.h"


#include "OXQuickString.h"
#include "OXHashTable.h"

#if _MSC_VER >= 1200
#pragma warning(push, 3)    // vector does not compile clean under W4
#pragma warning (disable : 4018)
#include <vector>
#pragma warning(pop)
#else
#include <vector>
#endif
#include <tchar.h>



///////////////////////////////////////////////////////////////////////
// Forward declarations

class  COXAttribute;          // Holds name/value pairs
class  COXParserObject;       // A single Object (either text, element, markup etc)
class  COXParserElement;      // A single element in the parsed tree
                            // COXParserElements have COXAttribute's associated with 
                            // them, and contain other COXParserElements and COXParserObjects


///////////////////////////////////////////////////////////////////////
// type defs

// function type to report parser errors
typedef BOOL (*ParserErrorFn)(int nErrorCode, LPCTSTR szError, 
							  int nLine, int nColumn, 
                              DWORD dwData);

// Special character entities, such as &gt; ('>')
struct ParserEntity
{
    LPTSTR szName;     // the entity name (eg 'amp' or 'gt')
    LPTSTR szLiteral;  // Literal representation (eg '&' or '>')
};

// For saving the current buffer position
struct SAVEPOS
{
    LPTSTR pBuf;      // Saved position of buffer
    int    nLine;     // Saved line number
    int    nCol;      // Saved column number
};


///////////////////////////////////////////////////////////////////////
// COXToken declaration

class OX_CLASS_DECL COXToken
{
public:
    enum TagTypes
    {      
        UNKNOWN = -1,    
        OPEN_TAG_BRACKET,            // <
        OPEN_ENDTAG_BRACKET,         // >
        OPEN_PROCINSTR_BRACKET,      // <?
        CLOSE_PROCINSTR_BRACKET,     // ?>
        CLOSE_TAG_BRACKET,           // >
        CLOSE_EMPTYTAG_BRACKET,      // />
        OPEN_COMMENT_BRACKET,        // <!--
        OPEN_MARKUP_BRACKET,         // <!
        CLOSE_COMMENT_BRACKET,       // -->
        EQUAL_SIGN,                  // =
        QUOTE,                       // "
        APOSTROPHE,                  // '
        STRING,                      // <plain text>
    };

public:
    COXToken();
    ~COXToken();

    void Clear();
    void SetType(int nType) { m_nType = nType; }
    int  GetType() const    { return m_nType;  }

protected:
    int m_nType;  // token type
};


///////////////////////////////////////////////////////////////////////
// COXParserObject declaration

class OX_CLASS_DECL COXParserObject
{
public:
    enum { UNKNOWN = -1, ATTRIBUTE, CDATA, COMMENT, ELEMENT, 
		MARKUP, PLAINTEXT, PROCINSTR, RAWTEXT, };
 
public:
    COXParserObject();
    COXParserObject(COXParserElement* pParent, int nType, 
		LPCTSTR szText);
    virtual ~COXParserObject();

public:
    int     GetType() const { return m_nType; }
    void    SetType(int nNewType) { m_nType = nNewType; }

    UINT    GetFlags() const { return m_nFlags; }
    void    SetFlags(UINT nFlags) { m_nFlags = nFlags; }

    LPCTSTR GetText() const { return m_Text.GetString(); }

	// --- In  : szText - the new text
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Sets the text of the COXParserObject object
    BOOL    SetText(LPCTSTR szText);

	// --- In  : szText - the name to check
	//           bCaseSensitive - whether or not the check is case sensitive
	// --- Out :
	// --- Returns : TRUE if szText is then same as the Object's text
	// --- Effect : 
    BOOL    IsText(LPCTSTR szText, BOOL bCaseSensitive = FALSE);

	// --- In  : 
	// --- Out :
	// --- Returns : This objects parent element
	// --- Effect : 
    COXParserElement* GetParent() const;
    void SetParent(COXParserElement* pObject) { m_pParent = pObject;  }

protected:
    COXQuickString    m_Text;    // Either tag name, comment text, or literal text
    int             m_nType;   // Element, comment, literal text, or Attribute type
    COXParserElement* m_pParent; // The parent object to this object
    UINT            m_nFlags;  // General flags for use by derived classes 
};


///////////////////////////////////////////////////////////////////////
// COXAttribute declaration

class OX_CLASS_DECL COXAttribute : public COXParserObject
{
public:
    enum { ATTR_UNKNOWN = -1, ATTR_STRING, ATTR_INTEGER };

public:
    COXAttribute();
    COXAttribute(LPCTSTR szName, LPCTSTR szValue);
    COXAttribute(LPCTSTR szName, int nValue);
    virtual ~COXAttribute();


public:
    LPCTSTR GetName() const { return GetText(); }
    void    SetName(LPCTSTR szName) { SetText(szName);  }
    BOOL    IsName(LPCTSTR szName, 
					BOOL bCheckCase = FALSE) { return IsText(szName, bCheckCase); }

	// --- In  : szValue, - the name to check
	//           bCaseSensitive - whether or not the check is case sensitive
	// --- Out :
	// --- Returns : TRUE if szValue, is then same as the Object's value
	// --- Effect : 
    BOOL    IsValue(LPCTSTR szValue, BOOL bCheckCase = FALSE);


	// --- In  : 
	// --- Out :
	// --- Returns : The string value, or '\0' if no string value (or if this object
	//               is actually holds an integer value)
	// --- Effect : 
    LPCTSTR GetStringValue();
	
	// --- In  : 
	// --- Out :
	// --- Returns : The integer value, or 0 if this object actually holds a string value
	// --- Effect : 
    int     GetIntValue() const;

	// --- In  : sValue - new string value
	// --- Out :
	// --- Returns :
	// --- Effect : Sets the string value in the attribute object
    void    SetValue(LPCTSTR szValue);

    // --- In  : nValue - new integer value
	// --- Out :
	// --- Returns :
	// --- Effect : Sets the integer value in the attribute object
	void    SetValue(int nValue);

    int     GetAttributeType() const          { return m_nFlags;       }
    void    SetAttributeType(int nAttrType)   { m_nFlags = nAttrType;  }

	// --- In  : Attr - another COXAttribute object
	// --- Out :
	// --- Returns : 
	// --- Effect : copies the contents of one COXAttribute object to this object
    void operator=(COXAttribute& Attr);

protected:
    COXQuickString  m_szValue;
    int           m_nValue;
};


///////////////////////////////////////////////////////////////////////
// COXParserElement declaration

class OX_CLASS_DECL COXParserElement : public COXParserObject
{
public:
    COXParserElement();

	// --- In  : szName - initial element name
	// --- Out :
	// --- Returns :
	// --- Effect : constructs a element object and sets the name
    COXParserElement(COXParserElement* pParent, LPCTSTR szName);
    ~COXParserElement();

    int             NumObjects() const { return m_Objects.size();    }
    COXParserObject*  Object(int nIndex) const { return m_Objects[nIndex];   }

	// --- In  : nIndex - the 0-based position this object should be inserted
	//           pObject - object to add
	// --- Out :
	// --- Returns : the newly added object
	// --- Effect : Inserts the supplied object into this object
    COXParserObject*  InsertObject(int nIndex, COXParserObject* pObject);

    // --- In  : pObject - object to add
	// --- Out :
	// --- Returns : the newly added object
	// --- Effect : Adds the supplied object to this object
	COXParserObject*  AddObject(COXParserObject* pObject);

    // --- In  : nIndex - the 0-based position this object should be moved to
	//           pObject - object to move
	// --- Out :
	// --- Returns : the moved object
	// --- Effect : Moves the supplied object to the indicated position. If the object
	//              does not already exist in the list of objects then it is inserted.
	COXParserObject*  MoveObject(int nIndex, COXParserObject* pObject);

	// --- In  : nIndex - the 0-based index of the element to remove
	// --- Out :
	// --- Returns : Returns TRUE on success
	// --- Effect : Deletes the specified element from the object.
    BOOL            DelObject(int nIndex);

    // --- In  : pElement - a pointer to the element to remove
	// --- Out :
	// --- Returns : Returns TRUE on success
	// --- Effect : Deletes the specified element from the object.
	BOOL            DelObject(COXParserObject* pObject);

    // --- In  : 
	// --- Out :
	// --- Returns :
	// --- Effect : Deletes all elements from the object
	void            ClearObjects();

	// --- In  : szName - the name of the element to add
	// --- Out :
	// --- Returns : Return the newly added element, or NULL on failure
	// --- Effect : Creates and adds a new element to object with the supplied name.
    COXParserElement* InsertElement(int nIndex, LPCTSTR szName);

	// --- In  : szName - the name of the element to add
	// --- Out :
	// --- Returns : Return the newly added element, or NULL on failure
	// --- Effect : Creates and adds a new element to object with the supplied name.
    COXParserElement* AddElement(LPCTSTR szName);

	// --- In  : szSearchName - name of the element to find. This can be in the
	//                          form "Level1\\Level2", in which case the function
	//                          will search down the Parser tree for reqiured nodes.
	//           bCaseSensitive - search is case sensitive iff this is true
	// --- Out :
	// --- Returns : Returns either the found element, or NULL on failure
	// --- Effect : Finds the specified element in the object
    COXParserElement* FindElement(LPCTSTR szName, 
		BOOL bCaseSensitive = FALSE);

    int             NumAttributes() const { return m_Attributes.size();    }
    COXAttribute*   Attribute(int nIndex) const { return m_Attributes[nIndex];   }

	// --- In  : pValue - new COXAttribute pointer to add
	// --- Out :
	// --- Returns : Returns the newly added attribute
	// --- Effect : Adds the supplied attribute to the element
    COXAttribute*     AddAttribute(COXAttribute* pAttribute);

	// --- In  : szName - the name of the value to add
	//           szValue - the string value to add
	// --- Out :
	// --- Returns : Return the newly added Attribute, or NULL on failure
	// --- Effect : Creates and adds a new Attribute object with the supplied name.
    COXAttribute*     AddAttribute(LPCTSTR szName, LPCTSTR szValue);

    // --- In  : szName - the name of the value to add
	//           nValue - the integer value to add
	// --- Out :
	// --- Returns : Return the newly added attribute, or NULL on failure
	// --- Effect : Creates and adds a new attribute object with the supplied name.
	COXAttribute*     AddAttribute(LPCTSTR szName, int nValue);

	// --- In  : nIndex - the 0-based index of the attributes to remove
	// --- Out :
	// --- Returns : Returns TRUE on success
	// --- Effect : Deletes the specified attributes from the object.
    BOOL            DelAttribute(int nIndex);
    
	// --- In  : pAttribute - a pointer to the attributes object to remove
	// --- Out :
	// --- Returns : Returns TRUE on success
	// --- Effect : Deletes the specified attributes from the object.
	BOOL            DelAttribute(COXAttribute* pAttribute);

    // --- In  : 
	// --- Out :
	// --- Returns :
	// --- Effect : Deletes all attributes from the object
	void            ClearAttributes();

	// --- In  : szName - name of the attributes to find
	//           bCaseSensitive - search is case sensitive iff this is true
	// --- Out :
	// --- Returns : Returns either the found attributes, or NULL on failure
	// --- Effect : Finds the specified attributes in the object that has the 
	//              specified name and string value.
    COXAttribute*     FindAttribute(LPCTSTR szName, 
						bool bCaseSensitive = false);

    // --- In  : szName - name of the attributes to find
	//           szValue - value of the attributes to find
	//           bCaseSensitive - search is case sensitive iff this is true
	// --- Out :
	// --- Returns : Returns either the found attributes, or NULL on failure
	// --- Effect : Finds the specified attributes in the object that has the 
	//              specified name and string value.
	COXAttribute*     FindAttribute(LPCTSTR szName, LPCTSTR szValue, 
						bool bCaseSensitive = false);

    // --- In  : szName - name of the attributes to find
	//           nValue - value of the attributes to find
	//           bCaseSensitive - search is case sensitive iff this is true
	// --- Out :
	// --- Returns : Returns either the found attributes, or NULL on failure
	// --- Effect : Finds the specified attributes in the object that has the 
	//              specified name and string value.
	COXAttribute*     FindAttribute(LPCTSTR szName, int nValue, 
						bool bCaseSensitive = false);

    LPCTSTR         GetName() { return GetText();}
    void            SetName(LPCTSTR szName) { SetText(szName); }
    BOOL            IsName(LPCTSTR szName, BOOL bCheckCase = FALSE) 
                               { return IsText(szName, bCheckCase);}

    void           Clear() { ClearObjects(); ClearAttributes(); }

protected:
    std::vector<COXParserObject*> m_Objects;
    std::vector<COXAttribute*>    m_Attributes;
};

///////////////////////////////////////////////////////////////////////
// COXParser declaration

class OX_CLASS_DECL COXParser
{
public:
    enum ErrorTypes
    {
        ERROR_FIRST = 100,          // All error messages start
        ERROR_NULL_BUFFER,          // null buffer passed in
        ERROR_END_OF_BUFFER,        // unexpected end of buffer
        ERROR_OUT_OF_MEMORY,        // Out of memory
        ERROR_BAD_TOKEN,            // Unable to retrieve a token
        ERROR_ILLEGAL_CHAR,         // Illegal characters encountered in token
        ERROR_UNEXPECTED_TOKEN,     // Unexpected token type
        ERROR_MISSING_END_TAG,      // Missing end tag
        ERROR_BAD_ENTITY,           // Bad entity string
        ERROR_BAD_INTEGER,          // Bad integer value
        ERROR_MISSING_END_BRACKET,  // Missing end bracket in tag
        ERROR_LAST,                 // All error messages end

        WARNING_FIRST = 200,        // All warnings start
        WARNING_UNEXPECTED_END_TAG, // Unexpected end tag
        WARNING_LAST,               // All warnings end
    };

// Construction
public:
	COXParser();
	virtual ~COXParser();

// Operations
public:

	// --- In  : ptr - NULL terminated character buffer to be parsed
	// --- Out :
	// --- Returns : Returns TRUE on success, FALSE otherwise
	// --- Effect : Parses the supplied buffer and stores the results in a tree
	//              of COXParserElement and COXAttribute objects
    BOOL Parse(LPTSTR ptr);

	// --- In  : szFile - name of the file to parse
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Loads and parses the supplied file and stores the results in a tree
    BOOL ParseFile(LPCTSTR szFile);

	// --- In  : szFile - name of the file to write
	// --- Out :
	// --- Returns : TRUE on success.
	// --- Effect : Stores the contents of the parse tree in a file.
    BOOL WriteFile(LPCTSTR szFile);

	// --- In  : 
	// --- Out :
	// --- Returns :
	// --- Effect : resets the parser object ot an empty state
    virtual void Clear();

// Attributes
public:
    COXParserElement* Root()                 { return &m_Root;           }

	// --- In  : 
	// --- Out :
	// --- Returns : Returns TRUE if the parser tree is empty.
	// --- Effect : 
    BOOL IsEmpty() const;

	// --- In  : 
	// --- Out :
	// --- Returns : Returns TRUE if the parsing is casesensitive.
	// --- Effect : 
    BOOL CaseSensitive() const { return m_bCaseSensitive;  }
    
	// --- In  : bCase - FALSE for non-casesensitive parsing, otherwise - TRUE. 
	// --- Out :
	// --- Returns : 
	// --- Effect : 
	void SetCaseSensitive(BOOL bCase)      { m_bCaseSensitive = bCase; }

	// --- In  : pFn - the error function to be called when an error occurs
	//           dwData - application specific data that is passed to the error function 
	// --- Out :
	// --- Returns : 
	// --- Effect : Sets the error function that will be called when an error occurs. The 
	//              function must have the form
	//
	//                  void ErrorFn(LPCTSTR szError, int nLine, int nColumn, DWORD dwData)
	//             
	//              where szError is a string containing an error message,
	//                    nLine, nColumn are the line and col number where the error ocurred,
	//                    dwData is the data supplied to SetErrorRptFunction.
    void SetErrorRptFunction(ParserErrorFn pFn, DWORD dwData);
    
	// --- In  : nErrorCode - error code. 
	// --- Out :
	// --- Returns : text representation of the error
	// --- Effect : converts error code to string representation
	virtual LPCTSTR TranslateErrorCode(int nErrorCode);

// Overridables for deriving new parsers
public:

	// --- In  : 
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Initializes the parser object in preparation for parsing
    virtual BOOL Initialize();

	// --- In  : 
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Cleans up the parser object after parsing
    virtual BOOL Cleanup();

	// --- In  : pParent - The element containing this markup entry
	// --- Out : 
	// --- Returns : A pointer to a new COXParserObject that contains the PI
	// --- Effect : Parses the Processing Instruction ("<?...?>") and adds the entry to 
	//              the element
    virtual COXParserObject* ParseProcessingInstruction(
		COXParserElement* pParent);

	// --- In  : pParent - The element containing this markup entry
	// --- Out : 
	// --- Returns : A pointer to a new COXParserObject that contains the markup entry
	// --- Effect : Parses the markup ("<!...>") and adds the entry to the element. If the
	//              markup contains a <!DOCTYPE tag, then this is parsed and stored, but
	//              not processed.
    virtual COXParserObject* ParseMarkup(COXParserElement* pParent);

	// --- In  : pParent - The element containing this comment
	// --- Out : 
	// --- Returns : A pointer to a new COXParserObject that contains the comment
	// --- Effect : Parses the comment ("<!--...-->") and adds the comment to the element
    virtual COXParserObject* ParseComment(COXParserElement* pParent);

	// --- In  : pParent - The element containing this text entry
	// --- Out : 
	// --- Returns : A pointer to a new COXParserObject that contains the text entry
	// --- Effect : Parses free text. Text parsing will stop when the first "<" 
	//              is found (regardless of quotes). On entry it is assumed that 
	//              m_Token will contain the first piece of text
    virtual COXParserObject* ParseText(COXParserElement* pParent);

	// --- In  : pParent - The parent of the element whose tag is being parsed
	// --- Out : bEmptyTag - will be set as true if this is an empty tag ("<.../>")
	// --- Returns : Returns a new COXParserElement object for this tag/element
	// --- Effect : Parses the tag for this element, and adds all attributes to the element
    virtual COXParserElement* ParseStartTag(COXParserElement* pParent, 
		BOOL& bEmptyTag);

	// --- In  : szCurrentTag - tag name for element being processed
	//           szNewTag - The new tag found (could be beginning or ending tag)
	// --- Out : 
	// --- Returns : Returns TRUE if a missing end tag has been detected and should
	//               be inserted
	// --- Effect : This function is called each time a new start or end tag is found.
	//              If the characteristics of the Current tag and the new tag show
	//              that there is a missing end tag for the current element then this 
	//              function should return TRUE in order to ensure the elements are 
	//              inserted into the main tree correctly.
	//              szNewTag may be NULL if this function is being called after the
	//              end-of-buffer has been reached.
    virtual BOOL IsEndTagMissing(LPCTSTR szCurrentTag, LPCTSTR szNewTag, 
                                 BOOL NewTagIsEndTag);

	// --- In  : pElement - The element containing the tag to test
	//           bEmptyTag - TRUE if the element is an empty element
	// --- Out : 
	// --- Returns : Returns TRUE if this element/tag should be ignored.
	// --- Effect : This function is called each time a new start tag is found. If 
	//              the characteristics of the tag indicate it should be ignored 
	//              then this function should return TRUE in order to ensure the 
	//              element is disposed of and processing can continue on normally.
	//              This is useful in allowing derived classes to handle elements
	//              in a non-standard manner, such as treating text modifying tags 
	//              in HTML (like <strong>) as "toggles" instead of actual XML nodes.
    virtual BOOL IgnoreStartTag(COXParserElement* pElement, 
		BOOL bEmptyTag);

	// --- In  : szEndTag - The name of the end tag
	// --- Out : 
	// --- Returns : Returns TRUE if this end tag should be ignored.
	// --- Effect : This function is called each time an end tag is found. If 
	//              the characteristics of the tag indicate it should be ignored 
	//              then this function should return TRUE in order to ensure the 
	//              end tag is ignored and processing can continue on normally.
	//              This is useful in allowing derived classes to handle elements
	//              in a non-standard manner, such as treating text modifying tags 
	//              in HTML (like </strong>) as "toggles" instead of actual XML nodes.
    virtual BOOL IgnoreEndTag(LPCTSTR szEndTag);

	// --- In  : pElement - The element to which an object will be added
	//           pObject - object ot add to element
	// --- Out : 
	// --- Returns : 
	// --- Effect : Adds an object ot an element
    virtual void AddObjectToElement(COXParserElement* pElement, 
		COXParserObject* pObject);

	// --- In  : pElement - The element whose attributes are being parsed
	// --- Out : 
	// --- Returns : Returns TRUE on success, FALSE otherwise
	// --- Effect : Parses the attributes for the tag for this element, and adds all 
	//              attributes to the element
    virtual BOOL ParseAttributes(COXParserElement* pElement);

	// --- In  : pElement - storage for this element
	//           nLevel - The depth of this element. Root node = level 0.
	// --- Out : 
	// --- Returns : Returns TRUE on success, FALSE otherwise
	// --- Effect : Recursively parses the text pointed to by pBuf. pBuf is incremented
	//              as the text gets parsed. As comments, text and other sub-elements of
	//              this element are found they are added, and all subelements recursively
	//              parsed and added.
    virtual BOOL ParseElement(COXParserElement *pElement, int nLevel);

	// --- In  : pElement - current element being parsed
	// --- Out : strEndTag - will contain the end tag name that was found.
	// --- Returns : Returns TRUE on success, FALSE otherwise
	// --- Effect : Parses the endtag ("</...>") for this element 
    virtual BOOL ParseEndTag(COXParserElement *pElement, 
		COXQuickString& strEndTag);

	// --- In  : szStr - literal identifier of a special character
	// --- Out : 
	// --- Returns : The literal character represented by the token name
	// --- Effect : Takes an identifier and returns the literal char. eg "gt" returns '>'
	//              Note that the current line and column number may not be accurate
	//              if ReportError is called from within this function
    virtual LPCTSTR GetLiteralString(LPCTSTR szStr);

	// --- In  : ch - character to check
	// --- Out : 
	// --- Returns : Returns a string containing the entity name for this character.
	// --- Effect : Looks through the m_Entity list for an entity whose literal
	//              representation is the same as the given character (in other words
	//              the lit. repr. must be a single character)
    virtual LPTSTR GetCharEntity(TCHAR ch);

	// --- In  : szStr - pointer to a text string
	// --- Out : 
	// --- Returns : Returns a COXQuickString object containing the encoded string.
	// --- Effect : Converts a string containing special chars (eg '<') to their char 
	//              entity equivalent, and returns a new string with a new decoded string
	//              Note that the current line and column number may not be accurate
	//              if ReportError is called from within this function
    virtual const COXQuickString EncodeText(LPCTSTR szStr);

	// --- In  : hFile - HANDLE of the file to write to
	//           pElement - element to output
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : outputs the attribute list of a single element
    virtual BOOL WriteAttributes(HANDLE hFile, 
		COXParserElement* pElement);

	// --- In  : hFile - HANDLE of the file to write to
	//           pObject - comment object to output
	//           nLevel - level of indentation
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : outputs the contents of a single object
    virtual BOOL WriteCData(HANDLE hFile, COXParserObject* pObject, 
		int nLevel);

	// --- In  : hFile - HANDLE of the file to write to
	//           pObject - comment object to output
	//           nLevel - level of indentation
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : outputs the contents of a single object
    virtual BOOL WriteComment(HANDLE hFile, COXParserObject* pObject, 
		int nLevel);

	// --- In  : hFile - HANDLE of the file to write to
	//           pElement - element to output
	//           nLevel - level of indentation
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : outputs the contents of a single element (recursive function)
    virtual BOOL WriteElement(HANDLE hFile, COXParserElement* pElement, 
		int nLevel);

	// --- In  : hFile - HANDLE of the file to write to
	//           pObject - comment object to output
	//           nLevel - level of indentation
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : outputs the contents of a single object
    virtual BOOL WriteMarkup(HANDLE hFile, COXParserObject* pObject, 
		int nLevel);

	// --- In  : hFile - HANDLE of the file to write to
	//           pObject - comment object to output
	//           nLevel - level of indentation
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : outputs the contents of a single object
    virtual BOOL WriteProcessingInstruction(HANDLE hFile, 
		COXParserObject* pObject, int nLevel);

	// --- In  : hFile - HANDLE of the file to write to
	//           pObject - text object to output
	//           nLevel - level of indentation
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : outputs the contents of a single object
    virtual BOOL WriteText(HANDLE hFile, COXParserObject* pObject, 
		int nLevel);

	// --- In  : hFile - HANDLE of the file to write to
	//           pObject - object to output
	//           nLevel - level of indentation
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : outputs the contents of a single object
    virtual BOOL WriteObject(HANDLE hFile, COXParserObject* pObject, 
		int nLevel);

protected:
	void InsertEntityValue(COXQuickString& str, LPCTSTR lpszEntity);

	// --- In  : 
	// --- Out :  A COXQuickString object containing the name 
	// --- Returns : TRUE on success
	// --- Effect : Retrieves a string delimted by the given quote character
    BOOL GetNameToken(COXQuickString& str);

	// --- In  : 
	// --- Out :  nNumber - a reference to an int variable to hold the parsed value
	// --- Returns : TRUE on success
	// --- Effect : Retrieves a number (optionally prefixed by + or -)
    BOOL GetNumberToken(int& nNumber);

	// --- In  : chQuoteChar - the quote character (" or ') that delimits the string
	// --- Out : A COXQuickString object containing the string 
	// --- Returns : TRUE on success
	// --- Effect : Retrieves a string delimted by the given quote character
    BOOL GetStringToken(COXQuickString& str, TCHAR chQuoteChar);

	// --- In  : bWarnOnEOF - if TRUE, a warning will be issued if EOF is encountered.
	// --- Out : token - a COXToken object that will be filled with the next token
	// --- Returns : Returns TRUE on success, FALSE otherwise
	// --- Effect : Retrieves the next token in the stream and moves the buffer 
	//              pointer immediately after token
    BOOL GetToken(COXToken& token, BOOL bWarnOnEOF = FALSE);

	// --- In  : 
	// --- Out : pos - Will be set to the current buffer position
	// --- Returns : 
	// --- Effect : Saves the current buffer position
    void SaveBufferPos(SAVEPOS& pos);

	// --- In  : pos - a previously saved buffer position structure
	// --- Out : 
	// --- Returns : 
	// --- Effect : Restores the previously saved the current buffer position
    void RestoreBufferPos(SAVEPOS& pos);

	// --- In  : nSteps - number of character positions to step the buffer
	//           bWarnOnError - if TRUE, then a warning is issued on an error
	// --- Out :
	// --- Returns : The next available char in the input stream, or 0 if none
	// --- Effect : moves the pointer to the buffer nSteps. Keeps track of column
	//              and line numbers, and returns the character in the buffer that
	//              is nSteps after the last character retrieved.
    TCHAR GetNextChar(int nSteps = 1, BOOL bWarnOnError = FALSE);

	// --- In  :
	// --- Out : 
	// --- Returns : TRUE if successful, FALSE otherwise
	// --- Effect : Moves the pointer to the first non-whitspace character in the input
	//              buffer. The 
    BOOL  RemoveWhiteSpace();

	// --- In  : nSteps - number of character positions to step back the buffer
	// --- Out : 
	// --- Returns : 
	// --- Effect : Moves the input pointer to back one character.
    void  UngetChar(int nSteps = 1);

	// --- In  : szFile - name of file to load
	// --- Out :
	// --- Returns : a pointer to the buffer containing the file text, or NULL on failure.
	// --- Effect : Loads the contents of a file to the supplied buffer. 
	//              The returned buffer MUST be free'd using GlobalFree
    LPTSTR LoadFile(LPCTSTR szFile);

	// --- In  : hFile - HANDLE of the file to write to
	//           nLevel - level of indentation
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Outputs indents according to the depth of the parse tree being output
    BOOL WriteTabs(HANDLE hFile, int nLevel);

	// --- In  : nErrorCode - not used yet. Will be used for an error code.
	//           fmt - error message format - used in the same way as a "printf"
	// --- Out :
	// --- Returns : Not used yet. In future this value will be used to determine whether
	//               or not processing should continue;
	// --- Effect : Used to signal that an error has occurred in processing. This routine
	//              calls the installed error handling function.
    BOOL ReportError(UINT nErrorCode, LPCTSTR fmt, ...);

	// --- In  : nErrorCode - Contains the error code.
	//           szError -  a string descibing the error
	//           nLine, nColumn - the current line and column number
	//           dwData - user supplied data provided in the call to SetErrorRptFunction
	// --- Out :
	// --- Returns : Not used yet. In future this value will be used to determine whether
	//               or not processing should continue;
	// --- Effect : This is the default routine used to report that an error has occurred 
	//              in processing. This routine can be replaced using SetErrorRptFunction.
    virtual BOOL DefErrorHandler(UINT nErrorCode, LPCTSTR szError, 
		int nLine, int nColumn, DWORD dwData);

protected:
    TCHAR m_chStartDelim;   // < 
    TCHAR m_chEndDelim;     // /
    TCHAR m_chTagEnd;       // >
    TCHAR m_chMarkup;       // !
    TCHAR m_chProcInstr;    // ?
    TCHAR m_chDash;         // -
    TCHAR m_chCR;           // \r
    TCHAR m_chLF;           // \n
    TCHAR m_chNULL;         // \0
    TCHAR m_chEsc;          // &

    LPCTSTR m_szTab;        // some spaces for tabbing
    UINT  m_nLineLength;    // Max length of a line of text when writing files

    static ParserEntity m_Entity[];      // nbsp, apos, gt etc
    COXHashTable m_EntityTable;

    BOOL m_bCaseSensitive;      // Is the parser case sensitive on tags?
    BOOL m_bErrorOnMissingTag;  // Flag an error on a missing end tag

    COXParserElement m_Root;  // The root element
    COXToken m_Token;         // Current token

    LPTSTR m_pBufStart;     // Pointer to start of input buffer
    LPTSTR m_pBuf;          // Pointer to current position in buffer
    int    m_nLine;         // Current line number
    int    m_nColumn;       // Current column

    ParserErrorFn m_pfnErrorFn;     // Error function to be supplied to parser
    DWORD m_dwErrData;              // Error function callback data for parser
};

#endif // !defined(_OXPARSER_H__)
