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
	UINT32  m_nProgress{ 0 };
	afx_msg void OnBnClickedCancel();
	virtual void PostNcDestroy();
	CProgressCtrl m_progressMeasure;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_staticTimer;
	CStatic m_staticPercent;
};
