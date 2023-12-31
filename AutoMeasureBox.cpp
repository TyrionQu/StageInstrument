// AutoMeasureBox.cpp : implementation file
//

#include "pch.h"
#include "StageInstrument.h"
#include "afxdialogex.h"
#include "AutoMeasureBox.h"
#include "MainFrm.h"


// CAutoMeasureBox dialog

IMPLEMENT_DYNAMIC(CAutoMeasureBox, CDialogEx)

CAutoMeasureBox::CAutoMeasureBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUTOMEASURE_BOX, pParent)
{
	ASSERT(pParent != NULL);

	m_pParent = pParent;
	m_nID = IDD_AUTOMEASURE_BOX;
}

CAutoMeasureBox::~CAutoMeasureBox()
{
}

void CAutoMeasureBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_BAR, m_staticTitle);
	DDX_Control(pDX, IDC_PROGRESS_MEASURE, m_progressMeasure);
	DDX_Control(pDX, IDC_STATIC_TIME, m_staticTimer);
	DDX_Control(pDX, IDC_STATIC_PERCENT, m_staticPercent);
}


BEGIN_MESSAGE_MAP(CAutoMeasureBox, CDialogEx)
	ON_BN_CLICKED(IDC_CANCEL, &CAutoMeasureBox::OnBnClickedCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAutoMeasureBox message handlers


BOOL CAutoMeasureBox::Create()
{
	return CDialogEx::Create(m_nID, m_pParent);
}

void CAutoMeasureBox::OnBnClickedCancel()
{
	((CMainFrame*)m_pParent)->DisableAutoMeasure();
	KillTimer(m_nTimer);
	DestroyWindow();
}


void CAutoMeasureBox::PostNcDestroy()
{
	delete this;
}


BOOL CAutoMeasureBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_progressMeasure.SetRange(0, 1000);
	m_progressMeasure.SetStep(5);

	m_nTimer = SetTimer(1, 1000, nullptr);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAutoMeasureBox::OnTimer(UINT_PTR nIDEvent)
{
	if (m_bPauseTimer) return;

	m_nProgress++;
	m_progressMeasure.SetPos(m_nProgress);
	CString strTimer(L"测量时间：00:00:00");
	UINT32 nHour = m_nProgress / 3600;
	UINT32 nLeft = m_nProgress % 3600;
	UINT32 nMin = nLeft / 60;
	UINT32 nSec = m_nProgress % 60;

	strTimer.Format(L"测量时间：%02d:%02d:%02d", nHour, nMin, nSec);

	m_staticTimer.SetWindowTextW(strTimer);
	CString strPercent;
	strPercent.Format(L"%0.1f%%", m_nProgress / 10.0);
	m_staticPercent.SetWindowTextW(strPercent);

	CDialogEx::OnTimer(nIDEvent);
}


LRESULT CAutoMeasureBox::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_TIMER)
	{
		OnTimer(wParam);
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}
