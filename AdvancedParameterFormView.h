#pragma once



// CAdvancedParameterFormView form view

class CAdvancedParameterFormView : public CFormView
{
	DECLARE_DYNCREATE(CAdvancedParameterFormView)

public:
	CAdvancedParameterFormView();           // protected constructor used by dynamic creation
	virtual ~CAdvancedParameterFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADVANCED_PARAMETER_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	BOOL m_bInitialized{ FALSE };
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
};


