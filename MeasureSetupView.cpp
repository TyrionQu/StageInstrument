
#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
#include "MeasureSetupView.h"
#include "Resource.h"
#include "StageInstrument.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMeasureSetupView::CMeasureSetupView() noexcept
{
//	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CMeasureSetupView::~CMeasureSetupView()
{
}

BEGIN_MESSAGE_MAP(CMeasureSetupView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeasureSetupView message handlers

int CMeasureSetupView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create views:
	m_pwndMeasureParamView = new CMeasureParamFormView;
	if (!m_pwndMeasureParamView->Create(NULL, L"测量参数设置", AFX_WS_DEFAULT_VIEW, rectDummy, this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create Measure Parameter View\n");
		return -1;      // fail to create
	}

	return 0;
}

void CMeasureSetupView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CMeasureSetupView::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_pwndMeasureParamView->SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CMeasureSetupView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CMeasureSetupView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_pwndMeasureParamView->GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CMeasureSetupView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_pwndMeasureParamView->SetFocus();
}
