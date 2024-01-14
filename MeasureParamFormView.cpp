// MeasureParamFV.cpp : implementation file
//

#include "pch.h"
#include "StageInstrument.h"
#include "MeasureParamFormView.h"

#include "MainFrm.h"


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
	DDX_Text(pDX, IDC_EDIT_DURATION, m_nScanDuration);
	DDX_Text(pDX, IDC_EDIT_FORCE, m_nForce);
	DDX_Control(pDX, IDC_COMBO_MEASURE_RANGE, m_comboScanRange);
}

BEGIN_MESSAGE_MAP(CMeasureParamFormView, CFormView)
	ON_WM_DESTROY()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, &CMeasureParamFormView::SetToolTipText)
	ON_EN_KILLFOCUS(IDC_EDIT_FORCE, &CMeasureParamFormView::OnEnKillfocusEditForce)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_FORCE, &CMeasureParamFormView::OnEnChangeEditForce)
	ON_BN_CLICKED(IDC_BTN_MEASURE_OPTIONS, &CMeasureParamFormView::OnBnClickedBtnMeasureOptions)
	ON_BN_CLICKED(IDC_BTN_ADVANCE_OPTIONS, &CMeasureParamFormView::OnBnClickedBtnAdvanceOptions)
	ON_EN_CHANGE(IDC_EDIT_LENGTH, &CMeasureParamFormView::OnEnChangeEditLength)
	ON_EN_KILLFOCUS(IDC_EDIT_LENGTH, &CMeasureParamFormView::OnEnKillfocusEditLength)
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
	if (m_bInitialized) return;
	m_bInitialized = TRUE;
	CFormView::OnInitialUpdate();
	EnableScrollBarCtrl(SB_BOTH, FALSE);
	SetScrollSizes(MM_TEXT, CSize(0, 0));

	EnableToolTips(TRUE);

	// Set 1mm as default scan
	m_comboScanRange.SetCurSel(3);
	m_nForce = 3.0;
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

BOOL CMeasureParamFormView::SetToolTipText(UINT id, NMHDR* pToolTipStruct, LRESULT* pResult)
{
	UNREFERENCED_PARAMETER(id);
	*pResult = 0;

	TOOLTIPTEXT* pText = (TOOLTIPTEXT*)pToolTipStruct;
	HWND nID = (HWND)pToolTipStruct->idFrom;
	if (pText->uFlags & TTF_IDISHWND)
	{
		if (nID == NULL)
			return FALSE;

		int nEditID = ::GetDlgCtrlID(nID);

		switch (nEditID)
		{
		case IDC_EDIT_FORCE:
			_stprintf_s(pText->lpszText, sizeof(pText->szText) / sizeof(TCHAR), L"力大小在%.1f-%.1fmg之间", MIN_FORCE, MAX_FORCE);
			break;
		case IDC_EDIT_LENGTH:
			_stprintf_s(pText->lpszText, sizeof(pText->szText) / sizeof(TCHAR), L"扫描长度小于%d微米", MAX_SAMPLE_LENGTH);
			break;
		default:
			break;
		}
		return TRUE;
	}
	return FALSE;
}


void CMeasureParamFormView::OnEnKillfocusEditForce()
{
	UpdateForceEdit();
}


HBRUSH CMeasureParamFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor != CTLCOLOR_EDIT)
		return hbr;

	int nID = pWnd->GetDlgCtrlID();
	if (nID != IDC_EDIT_FORCE && nID != IDC_EDIT_LENGTH)
		return hbr;

	CDigitalEdit* pEdit = nullptr;
	switch (nID)
	{
	case IDC_EDIT_FORCE:
		pEdit = &m_editForce;
		break;
	case IDC_EDIT_LENGTH:
		pEdit = &m_editScanLength;
		break;
	default:
		break;
	}
	if (pEdit == nullptr)
		return hbr;

	if (pEdit->m_bWarning)
	{
		COLORREF warningColor(RGB(255, 175, 200));
		pDC->SetBkColor(warningColor);
		hbr = CreateSolidBrush(warningColor);
	}
	else
	{
		COLORREF white(RGB(255, 255, 255));
		pDC->SetBkColor(white);
		hbr = CreateSolidBrush(white);
	}
	return hbr;
}


void CMeasureParamFormView::OnEnChangeEditForce()
{
	UpdateForceEdit(TRUE);
}


void CMeasureParamFormView::UpdateForceEdit(BOOL bEditing)
{
	UpdateData(TRUE);
	if (m_nForce > MAX_FORCE)
		m_nForce = MAX_FORCE;
	else if (m_nForce < MIN_FORCE && m_nForce != 0)
	{
		if ((bEditing && m_nForce != 0) || !bEditing)
			m_nForce = MIN_FORCE;
	}
	else
	{
		m_editForce.m_bWarning = FALSE;
		m_editForce.Invalidate();
		return;
	}
	UpdateData(FALSE);
	m_editForce.m_bWarning = TRUE;

	m_editForce.Invalidate(TRUE);
}

void CMeasureParamFormView::UpdateScanLength(BOOL bEditing)
{
	UpdateData(TRUE);
	if (m_nScanLength > MAX_SAMPLE_LENGTH)
		m_nScanLength = MAX_SAMPLE_LENGTH;
	else if (m_nScanLength < MIN_SAMPLE_LENGTH)
	{
		if ((bEditing && m_nScanLength != 0) || !bEditing)
		{
			m_nScanLength = MIN_SAMPLE_LENGTH;
		}
	}
	else
	{
		m_editScanLength.m_bWarning = FALSE;
		m_editScanLength.Invalidate();
		return;
	}
	UpdateData(FALSE);
	m_editScanLength.m_bWarning = TRUE;

	m_editScanLength.Invalidate(TRUE);
}


void CMeasureParamFormView::OnBnClickedBtnMeasureOptions()
{
	// Show detailed measure options pane
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (pMainFrame)
		pMainFrame->TiggerAdvancedSetting(pMainFrame->m_wndMeasureSetupBar.m_nDetaiedGroup);
}


void CMeasureParamFormView::OnBnClickedBtnAdvanceOptions()
{
	// Show advanced options pane
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (pMainFrame)
		pMainFrame->TiggerAdvancedSetting(pMainFrame->m_wndMeasureSetupBar.m_nAdvanceGroup);
}


void CMeasureParamFormView::OnEnChangeEditLength()
{
	UpdateScanLength(TRUE);
}


void CMeasureParamFormView::OnEnKillfocusEditLength()
{
	UpdateScanLength();
}
