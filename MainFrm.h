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

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "BasicParameterPane.h"
#include "MeasureSetupBar.h"
#include "PropertiesWnd.h"
#include "AutoMeasureBox.h"

#include "CryptoppVikey/CryptoppVikey.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"   // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h"  // support for user defined types


class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame() noexcept;

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CMFCShellTreeCtrl m_wndTree;
	CBasicParameterPane  m_wndBasicParamPane;
	CMeasureSetupBar  m_wndMeasureSetupBar;
	CPropertiesWnd    m_wndProperties;
	CAutoMeasureBox*  m_pAutoMeasureBox{ nullptr };
	BOOL              m_bStartButton{ TRUE };
	BOOL              m_bPauseButton{ FALSE };
	BOOL              m_bResume{ FALSE };
	BOOL              m_bStopButton{ FALSE };

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnWindowManager();
	afx_msg void OnOptions();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons();
public:
	afx_msg void OnBtnStart();
	afx_msg void OnBtnPause();
	afx_msg void OnBtnStop();
	void DisableAutoMeasure();
	afx_msg void OnUpdateBtnPause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnStop(CCmdUI* pCmdUI);
	afx_msg void OnBtnScanSettings();
	void TiggerAdvancedSetting(UINT nOption);

private:
	void OnVikeyTimerEvent();
	void OnUpdateTimerEvent();

	bool m_bNeedToPop;
#ifndef _DEBUG
	CryptoppVikey m_vikey;
#endif
	std::shared_ptr<spdlog::logger> m_logger;
};


