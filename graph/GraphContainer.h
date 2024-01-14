// GraphContainer.h : header file
//
#pragma once

#include "gruler.h"
#include "GraphPanel.h"

struct SGraphChange;

/////////////////////////////////////////////////////////////////////////////
// CGraphContainer window

class CGraphContainer : public CWnd
{
// Construction
public:
	CGraphContainer();

// Attributes
public:

    FVRuler vruler;
    FHRuler hruler;
    CGraphPanel* graph_panel;

// Operations
public:

    void UpdateWindows(unsigned long what_to_update);
    void UpdateViews(DWORD message_id, void* param);
    DWORD GetGraphFlags();
    void GetGraphWorldCoords(double* x1, double* x2, double* y1, double* y2);

    void DrawGraphToDC(CDC* dest_dc, CRect& rect_to_draw);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphContainer)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphContainer();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphContainer)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
