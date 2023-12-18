// MeasureOptionsBox.cpp : implementation file
//

#include "pch.h"
#include "StageInstrument.h"
#include "afxdialogex.h"
#include "MeasureOptionsBox.h"


// CMeasureOptionsBox dialog

IMPLEMENT_DYNAMIC(CMeasureOptionsBox, CDialogEx)

CMeasureOptionsBox::CMeasureOptionsBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEASURE_PORP_BOX, pParent)
{

}

CMeasureOptionsBox::~CMeasureOptionsBox()
{
}

void CMeasureOptionsBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MEASURE_OPTIONS, m_tabOptions);
}


BEGIN_MESSAGE_MAP(CMeasureOptionsBox, CDialogEx)
END_MESSAGE_MAP()


// CMeasureOptionsBox message handlers


BOOL CMeasureOptionsBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	TCITEM tcItem;

	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("通用");
	m_tabOptions.InsertItem(0, &tcItem);

	tcItem.pszText = _T("坐标");
	m_tabOptions.InsertItem(1, &tcItem);

	tcItem.pszText = _T("图形");
	m_tabOptions.InsertItem(2, &tcItem);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
