// GraphFrame.h : header file
//
#pragma once

#include "GraphContainer.h"
#include "pviewbar.h"
#include "graph_general.h"

/////////////////////////////////////////////////////////////////////////////
// CGraphFrame frame

class CGraphFrame : public CFrameWnd, public virtual CGraphBaseClass
{
	DECLARE_DYNCREATE(CGraphFrame)
protected:
	CGraphFrame();           // protected constructor used by dynamic creation

// Attributes
public:

    CGraphContainer graph_container;
    CPointViewBar pview_bar;
    BOOL m_bOwnTimer;

// Operations
public:

    BOOL Create(LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd, 
	BOOL bOwnTimer = FALSE, DWORD dwStyle = WS_CHILD | WS_VISIBLE);

    void OperateWithPointView(unsigned long pview_operations);
    void UpdateWindows(unsigned long what_to_update);
    void UpdateViews(DWORD message_id, void* param);
    DWORD GetGraphFlags(){return graph_container.GetGraphFlags();};
    void GetGraphWorldCoords(double* x1, double* x2, double* y1, double* y2)
    {
	graph_container.GetGraphWorldCoords(x1, x2, y1, y2);
    };

    void DrawGraphToDC(CDC* dest_dc, CRect& rect_to_draw);

    virtual void AppendMenuItems(CMenu* menu);
    virtual void OnRBMenuCommand(UINT command_id);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphFrame)
	public:
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
protected:

    void OnPointViewBarCommand(UINT nID);
    void OnPointViewUpdate(CCmdUI* pCmdUI);

	virtual ~CGraphFrame();

	// Generated message map functions
	//{{AFX_MSG(CGraphFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
