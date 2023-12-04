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
}


BEGIN_MESSAGE_MAP(CAutoMeasureBox, CDialogEx)
	ON_BN_CLICKED(IDC_CANCEL, &CAutoMeasureBox::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAutoMeasureBox message handlers


BOOL CAutoMeasureBox::Create()
{
	return CDialogEx::Create(m_nID, m_pParent);
}

void CAutoMeasureBox::OnBnClickedCancel()
{
	((CMainFrame*)m_pParent)->DisableAutoMeasure();
	DestroyWindow();
}


void CAutoMeasureBox::PostNcDestroy()
{
	delete this;
}
