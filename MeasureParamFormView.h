#pragma once

#include "DigitalEdit.h"

// CMeasureParamFormView form view

class CMeasureParamFormView : public CFormView
{
	DECLARE_DYNCREATE(CMeasureParamFormView)

public:
	BOOL m_bInitialized{ FALSE };
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

private:
	void UpdateForceEdit(BOOL bEditing = FALSE);
	void UpdateScanLength(BOOL bEditing = FALSE);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bExtendedPane{ FALSE };
	CDigitalEdit m_editScanLength;
	CDigitalEdit m_editDuration;
	CDigitalEdit m_editForce;
	UINT m_nScanLength;
	UINT m_nScanDuration;
	double m_nForce;
	CComboBox m_comboScanRange;
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnDestroy();
	afx_msg BOOL SetToolTipText(UINT id, NMHDR* pToolTipStruct, LRESULT* pResult);
	afx_msg void OnEnKillfocusEditForce();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditForce();
	afx_msg void OnBnClickedBtnMeasureOptions();
	afx_msg void OnBnClickedBtnAdvanceOptions();
	afx_msg void OnEnChangeEditLength();
	afx_msg void OnEnKillfocusEditLength();
};


