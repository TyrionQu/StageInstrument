// gen_prop_dlgs.h : header file
//

#pragma once

#include "..\resource.h"
#include "graphcombobox.h"
#include "graph_props.h"
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CAxisPropertyPage dialog

class CAxisPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CAxisPropertyPage)

	// Construction
public:
	CAxisPropertyPage();
	~CAxisPropertyPage();

	// Dialog Data
		//{{AFX_DATA(CAxisPropertyPage)
	enum { IDD = IDD_GRAPH_AXIS_PROP_PAGE };
	long	m_x_precision;
	CString	m_x_title;
	CString	m_x_uom;
	long	m_y_precision;
	CString	m_y_title;
	CString	m_y_uom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAxisPropertyPage)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAxisPropertyPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CGraphicsPropertyPage dialog

class CGraphPropsComboBox : public CGraphComboBox
{
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};

class CGraphicsPropertyPage : public CPropertyPage, public CGraphBaseClass
{
	DECLARE_DYNCREATE(CGraphicsPropertyPage)

	// Construction
public:
	CGraphicsPropertyPage();
	CGraphicsPropertyPage(CGraphWnd* main_wnd);
	~CGraphicsPropertyPage();

	// Dialog Data

	CArray<CGraphProps*, CGraphProps*> grprops;

	void SetActiveSel(int selnum);
	void SetHideShowAttr(int selnum);

	//{{AFX_DATA(CGraphicsPropertyPage)
	enum { IDD = IDD_GRAPH_GRAPHICS_PROPS };
	CGraphPropsComboBox	m_graph_combo;
	CString	m_graph_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsPropertyPage)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGraphicsPropertyPage)
	afx_msg void OnGraphChColor();
	afx_msg void OnGraphChTitle();
	afx_msg void OnGraphHideshow();
	afx_msg void OnGraphsShowall();
	afx_msg void OnSelchangeGraphChoice();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CGraphTitlePrompt dialog

class CGraphTitlePrompt : public CDialog
{
	// Construction
public:
	CGraphTitlePrompt(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
		//{{AFX_DATA(CGraphTitlePrompt)
	enum { IDD = IDD_GRAPH_CHANGE_TITLE };
	CString	m_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphTitlePrompt)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphTitlePrompt)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
