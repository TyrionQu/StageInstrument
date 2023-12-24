// MeasureParamFV.cpp : implementation file
//

#include "pch.h"
#include "StageInstrument.h"
#include "MeasureParamFormView.h"


// CMeasureParamFormView

IMPLEMENT_DYNCREATE(CMeasureParamFormView, CFormView)

CMeasureParamFormView::CMeasureParamFormView()
	: CFormView(IDD_MEASURE_PARAMETER_FORMVIEW)
	, m_nScanLength(0)
	, m_nScanDuration(0)
	, m_nForce(0)
{

}

CMeasureParamFormView::~CMeasureParamFormView()
{
}

void CMeasureParamFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LENGTH, m_editScanLength);
	DDX_Control(pDX, IDC_EDIT_DURATION, m_editDuration);
	DDX_Control(pDX, IDC_EDIT_FORCE, m_editForce);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_nScanLength);
	DDV_MinMaxUInt(pDX, m_nScanLength, 1, 5000);
	DDX_Text(pDX, IDC_EDIT_DURATION, m_nScanDuration);
	DDV_MinMaxUInt(pDX, m_nScanDuration, 1, 300);
	DDX_Text(pDX, IDC_EDIT_FORCE, m_nForce);
	DDV_MinMaxUInt(pDX, m_nForce, 1, 500);
	DDX_Control(pDX, IDC_COMBO_MEASURE_RANGE, m_comboScanRange);
}

BEGIN_MESSAGE_MAP(CMeasureParamFormView, CFormView)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMeasureParamFormView diagnostics

#ifdef _DEBUG
void CMeasureParamFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMeasureParamFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMeasureParamFormView message handlers


void CMeasureParamFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	EnableScrollBarCtrl(SB_BOTH, FALSE);
	SetScrollSizes(MM_TEXT, CSize(0, 0));

	// Set 1mm as default scan
	m_comboScanRange.SetCurSel(3);
	m_nForce = 3;
	m_nScanDuration = 10;
	m_nScanLength = 2000;

	UpdateData(0);
}


BOOL CMeasureParamFormView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CMeasureParamFormView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: Add your message handler code here
}
