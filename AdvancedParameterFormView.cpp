// CAdvancedParameterFormView.cpp : implementation file
//

#include "pch.h"
#include "StageInstrument.h"
#include "AdvancedParameterFormView.h"


// CAdvancedParameterFormView

IMPLEMENT_DYNCREATE(CAdvancedParameterFormView, CFormView)

CAdvancedParameterFormView::CAdvancedParameterFormView()
	: CFormView(IDD_ADVANCED_PARAMETER_FORMVIEW)
{

}

CAdvancedParameterFormView::~CAdvancedParameterFormView()
{
}

void CAdvancedParameterFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAdvancedParameterFormView, CFormView)
END_MESSAGE_MAP()


// CAdvancedParameterFormView diagnostics

#ifdef _DEBUG
void CAdvancedParameterFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdvancedParameterFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdvancedParameterFormView message handlers


BOOL CAdvancedParameterFormView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
