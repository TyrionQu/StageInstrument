
#pragma once

#include "MeasureDetailedParameterFormView.h"
#include "AdvancedParameterFormView.h"


class CMeasureSetupBar : public CMFCTasksPane
{
public:
	CMeasureSetupBar() noexcept;
	virtual ~CMeasureSetupBar();

	void OnChangeVisualStyle();

protected:
	// CFormView must be pointer, which will release in parent class automatically
	CMeasureDetailedParameterFormView* m_pwndDetailedView{ nullptr };
	CAdvancedParameterFormView* m_pwndAdvancedView{ nullptr };

	// Overrides
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// Disable resize dockable pane
//	virtual BOOL IsResizable() const { return FALSE; }
//	virtual BOOL IsRestoredFromRegistry() const { return FALSE; }

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

