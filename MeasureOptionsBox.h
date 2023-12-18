#pragma once
#include "afxdialogex.h"


// CMeasureOptionsBox dialog

class CMeasureOptionsBox : public CDialogEx
{
	DECLARE_DYNAMIC(CMeasureOptionsBox)

public:
	CMeasureOptionsBox(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CMeasureOptionsBox();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEASURE_PORP_BOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_tabOptions;
};
