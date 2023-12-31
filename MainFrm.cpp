// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "StageInstrument.h"

#include "MainFrm.h"
#include "Resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_COMMAND(ID_BTN_START, &CMainFrame::OnBtnStart)
	ON_COMMAND(ID_BTN_PAUSE, &CMainFrame::OnBtnPause)
	ON_COMMAND(ID_BTN_STOP, &CMainFrame::OnBtnStop)
	ON_UPDATE_COMMAND_UI(ID_BTN_PAUSE, &CMainFrame::OnUpdateBtnPause)
	ON_UPDATE_COMMAND_UI(ID_BTN_START, &CMainFrame::OnUpdateBtnStart)
	ON_UPDATE_COMMAND_UI(ID_BTN_STOP, &CMainFrame::OnUpdateBtnStop)
	ON_COMMAND(ID_BTN_SCAN_SETTINGS, &CMainFrame::OnBtnScanSettings)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Navigation pane will be created at left, so temporary disable docking at the left side:
//	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// create docking windows
//	if (!CreateDockingWindows())
//	{
//		TRACE0("Failed to create docking windows\n");
//		return -1;
//	}

//	m_wndBasicParamPane.EnableDocking(CBRS_ALIGN_LEFT);
//	DockPane(&m_wndBasicParamPane);
//	m_wndMeasureSetupBar.EnableDocking(CBRS_ALIGN_LEFT);
//	DockPane(&m_wndMeasureSetupBar);
	// It will introduce assert warning if try to fix pane windows
	// the following two lines will resolve it.
	// But it cause another problem, which will redraw view in unexpected position.
	// Before finding one better solution, this function must be disable
//	CDockingManager* pDockManager = GetDockingManager();
//	pDockManager->AddPane(&m_wndMeasureSetupBar);

//	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
//	DockPane(&m_wndProperties);


	// Outlook bar is created and docking on the left side should be allowed.
//	EnableDocking(CBRS_ALIGN_LEFT);
//	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);
	// set the visual manager and style based on persisted value
	CWaitCursor wait;
	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
	CDockingManager::SetDockingMode(DT_SMART);
	m_wndRibbonBar.SetWindows7Look(FALSE);
	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	// Enable enhanced windows management dialog
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// Switch the order of document name and application name on the window title bar. This
	// improves the usability of the taskbar because the document name is visible with the thumbnail.
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != nullptr);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}

BOOL CMainFrame::CreateDockingWindows()
{
	// Create class view
	CString strParamView(L"设置测量参数");

	// Create properties window
	CString strPropertiesWnd;
	BOOL bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons();
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons()
{
	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_CLASS_VIEW_HC), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndMeasureSetupBar.SetIcon(hClassViewIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_PROPERTIES_WND_HC), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}


void CMainFrame::OnBtnStart()
{
	if (m_pAutoMeasureBox == nullptr)
	{
		m_pAutoMeasureBox = new CAutoMeasureBox(this);
		theApp.CreateNewMeasureView();
		OnMDIWindowCmd(ID_WINDOW_TILE_VERT);
		if (m_pAutoMeasureBox->Create())
		{
			m_bStartButton = FALSE;
			m_bPauseButton = TRUE;
			m_bStopButton = TRUE;
			CRect curMainRect, curBoxRect;
			GetWindowRect(&curMainRect);
			m_pAutoMeasureBox->GetWindowRect(&curBoxRect);
			LONG boxWidth = curBoxRect.Width();
			LONG boxHeight = curBoxRect.Height();
			curBoxRect.left = curMainRect.left + (curMainRect.right - curMainRect.left) / 3;
			curBoxRect.top = curMainRect.top + (curMainRect.bottom - curMainRect.top) / 3;
			curBoxRect.right = curBoxRect.left + boxWidth;
			curBoxRect.bottom = curBoxRect.top + boxHeight;
			m_pAutoMeasureBox->MoveWindow(curBoxRect);
			m_pAutoMeasureBox->ShowWindow(SW_SHOW);

			// Redraw the framework
			UINT nflags = RDW_ALLCHILDREN | RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW;
			RedrawWindow(NULL, NULL, nflags);

		}
	}
	else
		m_pAutoMeasureBox->SetActiveWindow();
}


void CMainFrame::OnBtnPause()
{
	m_bStartButton = FALSE;
	m_bPauseButton = TRUE;
	m_bStopButton = TRUE;
	CMFCRibbonButton* pButton = DYNAMIC_DOWNCAST(CMFCRibbonButton, m_wndRibbonBar.FindByID(ID_BTN_PAUSE));
	if (pButton == NULL) return;

	m_bResume = !m_bResume;
	if (m_bResume)
	{
		pButton->SetText(L"继续");
		m_pAutoMeasureBox->m_bPauseTimer = TRUE;
		m_pAutoMeasureBox->ShowWindow(SW_HIDE);
	}
	else
	{
		pButton->SetText(L"暂停");
		m_pAutoMeasureBox->m_bPauseTimer = FALSE;
		m_pAutoMeasureBox->ShowWindow(SW_SHOW);
	}
}


void CMainFrame::OnBtnStop()
{
	m_bStartButton = TRUE;
	m_bPauseButton = FALSE;
	m_bStopButton = FALSE;
	m_pAutoMeasureBox->OnBnClickedCancel();
}

void CMainFrame::DisableAutoMeasure()
{
	m_pAutoMeasureBox = nullptr;
	m_bStartButton = TRUE;
	m_bPauseButton = FALSE;
	m_bStopButton = FALSE;
}

void CMainFrame::OnUpdateBtnPause(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bPauseButton);
}


void CMainFrame::OnUpdateBtnStart(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bStartButton);
}


void CMainFrame::OnUpdateBtnStop(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bStopButton);
}


void CMainFrame::OnBtnScanSettings()
{
	if (m_wndBasicParamPane.GetSafeHwnd())
	{
		BOOL bShow = !(m_wndBasicParamPane.IsVisible());
		m_wndBasicParamPane.ShowPane(bShow, FALSE, TRUE);
		RecalcLayout();
		return;
	}

	CString strParamView(L"设置测量参数");
	UINT nID = ID_BASIC_SCAN_PARAMETER_PANE;
	if (!m_wndBasicParamPane.Create(strParamView, this, CRect(0, 0, 260, 200), TRUE, nID, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Basic Measure Parameter window\n");
		return;
	}
	m_wndBasicParamPane.EnableDocking(CBRS_ALIGN_LEFT);
	DockPane(&m_wndBasicParamPane, AFX_IDW_DOCKBAR_LEFT);
	ShowPane(&m_wndBasicParamPane, TRUE, FALSE, TRUE);
	RecalcLayout();
}

void CMainFrame::TiggerAdvancedSetting(UINT nOption)
{
	// 0 for detailed setting, 1 for advanced setting
	if (m_wndMeasureSetupBar.GetSafeHwnd())
	{
		m_wndMeasureSetupBar.ShowPane(TRUE, FALSE, TRUE);
		if (nOption > 1) return;
		m_wndMeasureSetupBar.CollapseGroup(nOption, FALSE);
		RecalcLayout();
		return;
	}
	CString strParamView(L"高级测量参数");
	UINT nID = ID_ADVANCED_PARAMETER_PANE;
	if (!m_wndMeasureSetupBar.Create(strParamView, this, CRect(0, 0, 516, 200),
		TRUE, nID,
		WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_HIDE_INPLACE | WS_CAPTION,
		AFX_CBRS_OUTLOOK_TABS,
		AFX_CBRS_CLOSE))
	{
		TRACE0("Failed to create Advanced Measure Parameter window\n");
		return; // failed to create
	}
	m_wndMeasureSetupBar.EnableDocking(CBRS_ALIGN_LEFT);
	DockPane(&m_wndMeasureSetupBar, AFX_IDW_DOCKBAR_LEFT);
	ShowPane(&m_wndMeasureSetupBar, TRUE, FALSE, TRUE);
	if (nOption > 1) return;
	m_wndMeasureSetupBar.CollapseAllGroups();
	m_wndMeasureSetupBar.CollapseGroup(nOption, FALSE);
	RecalcLayout();
}