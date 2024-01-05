
#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
#include "MeasureSetupBar.h"
#include "Resource.h"
#include "StageInstrument.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMeasureSetupBar::CMeasureSetupBar() noexcept
{
}

CMeasureSetupBar::~CMeasureSetupBar()
{
}

BEGIN_MESSAGE_MAP(CMeasureSetupBar, CMFCTasksPane)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeasureSetupBar message handlers

int CMeasureSetupBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableOffsetCustomControls(FALSE);

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create views:
	m_pwndDetailedView = new CMeasureDetailedParameterFormView;
	DWORD dwStyle = WS_CHILD | WS_VISIBLE;
	if (!m_pwndDetailedView->Create(NULL, L"详细测量参数设置", dwStyle, rectDummy, this, AFX_IDW_PANE_FIRST + 1, NULL))
	{
		TRACE0("Failed to create Detailed Measure Parameter View\n");
		return -1;      // fail to create
	}

	m_pwndAdvancedView = new CAdvancedParameterFormView;
	if (!m_pwndAdvancedView->Create(NULL, L"详细测量参数设置", dwStyle, rectDummy, this, AFX_IDW_PANE_FIRST + 2, NULL))
	{
		TRACE0("Failed to create Detailed Measure Parameter View\n");
		return -1;      // fail to create
	}

	OnChangeVisualStyle();

	return 0;
}

BOOL CMeasureSetupBar::PreTranslateMessage(MSG* pMsg)
{
	return CMFCTasksPane::PreTranslateMessage(pMsg);
}

void CMeasureSetupBar::OnSetFocus(CWnd* pOldWnd)
{
	CMFCTasksPane::OnSetFocus(pOldWnd);

	m_pwndDetailedView->SetFocus();
}

void CMeasureSetupBar::OnChangeVisualStyle()
{
	int nGroup1 = AddGroup(_T("详细探测参数设置"), FALSE, TRUE);
	//AddWindow(nGroup1, m_pwndMeasureParamView->GetSafeHwnd(), 600);
	AddWindow(nGroup1, m_pwndDetailedView->GetSafeHwnd(), 420);
//	CollapseGroup(nGroup1, FALSE);

	int nGroup2 = AddGroup(_T("高级设置"), TRUE);
	AddWindow(nGroup2, m_pwndAdvancedView->GetSafeHwnd(), 720);
}
