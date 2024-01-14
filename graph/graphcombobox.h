// graphcombobox.h : header file
//
#pragma once

#include "graph_general.h"

/////////////////////////////////////////////////////////////////////////////
// CGraphComboBox window

class CGraphComboBox : public CComboBox, public virtual CGraphBaseClass
{
// Construction
public:
	CGraphComboBox();

// Attributes
public:

    BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );
    void DrawComboItem(COLORREF color, const TCHAR* title, LPDRAWITEMSTRUCT lpDrawItemStruct);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
