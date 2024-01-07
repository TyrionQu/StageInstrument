
#include "pch.h"
#include "framework.h"
#include "mainfrm.h"
#include "BasicParameterPane.h"
#include "Resource.h"
#include "StageInstrument.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CBasicParameterPane

CBasicParameterPane::CBasicParameterPane() noexcept
{
}

CBasicParameterPane::~CBasicParameterPane()
{
}

BEGIN_MESSAGE_MAP(CBasicParameterPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CBasicParameterPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create view:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	m_pwndMeasureParamView = new CMeasureParamFormView;
	if (!m_pwndMeasureParamView->Create(NULL, L"测量参数设置", WS_CHILD | WS_VISIBLE, rectDummy, this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create Measure Parameter View\n");
		return -1;      // fail to create
	}
	m_pwndMeasureParamView->OnInitialUpdate();

	OnChangeVisualStyle();

	AdjustLayout();

	return 0;
}

void CBasicParameterPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CBasicParameterPane::OnContextMenu(CWnd* pWnd, CPoint point)
{
}

void CBasicParameterPane::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

//	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

//	m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_pwndMeasureParamView->SetWindowPos(nullptr, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CBasicParameterPane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_pwndMeasureParamView->SetFocus();
}

void CBasicParameterPane::OnChangeVisualStyle()
{
}


