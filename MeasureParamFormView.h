#pragma once

#include "DigitalEdit.h"

// CMeasureParamFormView form view

class CMeasureParamFormView : public CFormView
{
	DECLARE_DYNCREATE(CMeasureParamFormView)

public:
	CMeasureParamFormView();           // protected constructor used by dynamic creation
	virtual ~CMeasureParamFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEASURE_PARAMETER_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDigitalEdit m_editScanLength;
	CDigitalEdit m_editDuration;
	CDigitalEdit m_editForce;
	UINT m_nScanLength;
	UINT m_nScanDuration;
	UINT m_nForce;
	CComboBox m_comboScanRange;
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnDestroy();
};


