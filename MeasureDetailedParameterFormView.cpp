// MeasureDetailedParameterFormView.cpp : implementation file
//

#include "pch.h"
#include "StageInstrument.h"
#include "MeasureDetailedParameterFormView.h"


// CMeasureDetailedParameterFormView

IMPLEMENT_DYNCREATE(CMeasureDetailedParameterFormView, CFormView)

CMeasureDetailedParameterFormView::CMeasureDetailedParameterFormView()
	: CFormView(IDD_DETAILED_PARAMETER_FORMVIEW)
	, m_nStylusForce(0)
{

}

CMeasureDetailedParameterFormView::~CMeasureDetailedParameterFormView()
{
}

void CMeasureDetailedParameterFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SCANTYPE, m_comboScanType);
	DDX_Control(pDX, IDC_COMBO_SCANRANGE, m_comboScanRange);
	DDX_Control(pDX, IDC_COMBO_SCANPROFILE, m_comboScanProfile);
	DDX_Control(pDX, IDC_COMBO_STYLUS_TYPE, m_comboStylusType);
	DDX_Control(pDX, IDC_EDIT_STYLUS_FORCE, m_editStylusForce);
	DDX_Control(pDX, IDC_EDIT_SAMPLE_LENGTH, m_editSampleLength);
	DDX_Control(pDX, IDC_EDIT_SCAN_DURATION, m_editScanDuration);
	DDX_Control(pDX, IDC_EDIT_SCAN_RESOLUTION, m_editResolution);
	DDX_Control(pDX, IDC_EDIT_SCAN_SAMPLE, m_editSample);
	DDX_Control(pDX, IDC_EDIT_SCAN_SAMPLE2, m_editSpeed);
	DDX_Text(pDX, IDC_EDIT_STYLUS_FORCE, m_nStylusForce);
}

BEGIN_MESSAGE_MAP(CMeasureDetailedParameterFormView, CFormView)
	ON_WM_CTLCOLOR()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, &CMeasureDetailedParameterFormView::SetToolTipText)
	ON_EN_CHANGE(IDC_EDIT_STYLUS_FORCE, &CMeasureDetailedParameterFormView::OnEnChangeEditStylusForce)
	ON_EN_KILLFOCUS(IDC_EDIT_STYLUS_FORCE, &CMeasureDetailedParameterFormView::OnEnKillfocusEditStylusForce)
END_MESSAGE_MAP()


// CMeasureDetailedParameterFormView diagnostics

#ifdef _DEBUG
void CMeasureDetailedParameterFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMeasureDetailedParameterFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMeasureDetailedParameterFormView message handlers


void CMeasureDetailedParameterFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}


HBRUSH CMeasureDetailedParameterFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_EDIT && pWnd->GetDlgCtrlID() == IDC_EDIT_FORCE)
	{
		if (m_editStylusForce.m_bWarning)
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

	return hbr;
}

BOOL CMeasureDetailedParameterFormView::SetToolTipText(UINT id, NMHDR* pToolTipStruct, LRESULT* pResult)
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
		case IDC_EDIT_STYLUS_FORCE:
			_stprintf_s(pText->lpszText, sizeof(pText->szText) / sizeof(TCHAR), L"����С��%.1f-%.1fmg֮��", MIN_FORCE, MAX_FORCE);
			break;
		default:
			break;
		}
		return TRUE;
	}
	return FALSE;
}

void CMeasureDetailedParameterFormView::UpdateForceEdit()
{
	UpdateData(TRUE);
	if (m_nStylusForce > MAX_FORCE)
		m_nStylusForce = MAX_FORCE;
	else if (m_nStylusForce < MIN_FORCE)
		m_nStylusForce = MIN_FORCE;
	else
	{
		m_editStylusForce.m_bWarning = FALSE;
		m_editStylusForce.Invalidate();
		return;
	}
	UpdateData(FALSE);
	m_editStylusForce.m_bWarning = TRUE;

	m_editStylusForce.Invalidate(TRUE);
}


void CMeasureDetailedParameterFormView::OnEnChangeEditStylusForce()
{
	UpdateForceEdit();
}


void CMeasureDetailedParameterFormView::OnEnKillfocusEditStylusForce()
{
	UpdateForceEdit();
}