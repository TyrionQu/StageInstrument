#pragma once
#include "afxdialogex.h"

#include "ColorStatic.h"


// CAutoMeasureBox dialog

class CAutoMeasureBox : public CDialogEx
{
private:
	using CDialogEx::Create;

	DECLARE_DYNAMIC(CAutoMeasureBox)

public:
	CAutoMeasureBox(CWnd* pParent);   // standard constructor
	virtual ~CAutoMeasureBox();
	BOOL Create();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOMEASURE_BOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CWnd* m_pParent;
	int m_nID;

	DECLARE_MESSAGE_MAP()
public:
	CColorStatic m_staticTitle;
	afx_msg void OnBnClickedCancel();
	virtual void PostNcDestroy();
};
