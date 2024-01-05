
#pragma once

#include "MeasureParamFormView.h"

class CBasicParameterPane : public CDockablePane
{
// Construction
public:
	CBasicParameterPane() noexcept;

	void AdjustLayout();
	void OnChangeVisualStyle();

// Attributes
protected:
	CMeasureParamFormView* m_pwndMeasureParamView{ nullptr };

protected:

// Implementation
public:
	virtual ~CBasicParameterPane();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

