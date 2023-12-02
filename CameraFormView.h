#pragma once

#include "DigitalEdit.h"

// CCameraFormView form view

class CCameraFormView : public CFormView
{
	DECLARE_DYNCREATE(CCameraFormView)

protected:
	CCameraFormView();           // protected constructor used by dynamic creation
	virtual ~CCameraFormView();
	HWND m_hCamera;

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERA_FORMVIEW };
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
	virtual void OnInitialUpdate();
	virtual void OnFinalRelease();
	CDigitalEdit m_editIntensity;
};


