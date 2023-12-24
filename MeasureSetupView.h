
#pragma once

#include "MeasureParamFormView.h"

class CMeasureSetupView : public CDockablePane
{
public:
	CMeasureSetupView() noexcept;
	virtual ~CMeasureSetupView();

	void AdjustLayout();
	void OnChangeVisualStyle();

protected:
	// CFormView must be pointer, which will release in parent class automatically
	CMeasureParamFormView* m_pwndMeasureParamView{ nullptr };


// Overrides
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

