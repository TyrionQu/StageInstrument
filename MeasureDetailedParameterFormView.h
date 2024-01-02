#pragma once

#include "DigitalEdit.h"


// CMeasureDetailedParameterFormView form view

class CMeasureDetailedParameterFormView : public CFormView
{
	DECLARE_DYNCREATE(CMeasureDetailedParameterFormView)

protected:
	CMeasureDetailedParameterFormView();           // protected constructor used by dynamic creation
	virtual ~CMeasureDetailedParameterFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DETAILED_PARAMETER_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	void UpdateForceEdit();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboScanType;
	CComboBox m_comboScanRange;
	CComboBox m_comboScanProfile;
	CComboBox m_comboStylusType;
	CDigitalEdit m_editStylusForce;
	CDigitalEdit m_editSampleLength;
	CDigitalEdit m_editScanDuration;
	CDigitalEdit m_editResolution;
	CDigitalEdit m_editSample;
	CDigitalEdit m_editSpeed;
	double m_nStylusForce;
	virtual void OnInitialUpdate();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL SetToolTipText(UINT id, NMHDR* pToolTipStruct, LRESULT* pResult);
	afx_msg void OnEnChangeEditStylusForce();
	afx_msg void OnEnKillfocusEditStylusForce();
};


